// 1. Escribir una consulta para calcular el promedio de puntuaciones de cada clase (class_id) y compararlo con el promedio general de todas las clases. La consulta debe devolver un documento para cada clase que incluya el class_id, el promedio de puntuaciones de esa clase y un campo adicional que indique si el promedio de la clase está por encima o por debajo del promedio general de todas las clases. Los resultados deben ordenarse de manera ascendente por class_id y de manera descendente por average_score.

db.grades.aggregate([
    {
        $unwind: "$scores"
    },
    {
        $project: {
            class_id: 1,
            score_avg: 1,
            scores: 1
        }
    },
    {
        $group: {
            _id: "$class_id",
            average_score: {
                $avg: "$scores.score"
            }
        }
    },
    {
        $lookup: {
            from: "grades",
            pipeline: [
               {
                $unwind: "$scores"
               },
               {
                $group: {
                    _id: null,
                    overall_average: {
                        $avg: "$scores.score"
                    }
                }
               }
            ],
            as: "overall_average"
        }
    },
    {
        $unwind: "$overall_average"
    },
    {
        $project: {
          class_id: "$_id",
          average_score: 1,
          comparison_to_overall_average: {
            $switch: {
                branches: [
                    {case: {$gt:[{$subtract:["$average_score", "$overall_average.overall_average"]}, 0]}, then: "above"},
                    {case: {$eq:[{$subtract:["$average_score", "$overall_average.overall_average"]}, 0]}, then: "equal"},
                    {case: {$lt:[{$subtract:["$average_score", "$overall_average.overall_average"]}, 0]}, then: "below"}
                ],
                default: null
            }
          },
          _id: 0
        }
    },
    {
        $sort: {
            class_id: -1,
            average_score: 1
        }
    }
]);

// 2. Actualizar los documentos en la colección grades, ajustando todas las puntuaciones para que estén normalizadas entre 0 y 7

db.grades.updateMany(
    {},
    [
        {
            $set: {
                scores: {
                    $map: {
                        input: "$scores",
                        as: "score",
                        in: {
                            score: {
                                $divide: [
                                    {$multiply: ["$$score.score", 7]},
                                    100
                                ]
                            },
                            type: "$$score.type"
                        }
                    }
                }
            }
        }
    ]
);

// CHECK
// db.grades.find()

// 3. Crear una vista "top10students_homework" que liste los 10 estudiantes con los mejores promedios para homework. Ordenar por average_homework_score descendiente.

db.createView(
    "top10students_homework",
    "grades",
    [
        {
            $unwind:"$scores"
        },
        {
            $match:{
                "scores.type": "homework"
            }
        },
        {
            $group: {
              _id: "$student_id",
              average_homework_score:{
                $avg:"$scores.score"
              }
            }
        },
        {
            $project:{
                student_id:"$_id",
                average_homework_score:1,
                _id:0
            }
        },
        {
            $sort:{
                average_homework_score: -1
            }
        },
        {
            $limit: 10
        }
    ]
);

// CHECK
// db.top10students_homework.find()

// 4. Especificar reglas de validación en la colección grades. El único requerimiento es que se valide que los type de los scores sólo puedan ser de estos tres tipos: [“exam”, “quiz”, “homework”]


db.runCommand({
    collMod: "grades",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["student_id", "scores", "class_id"],
            properties: {
                student_id: {
                    bsonType: "int",
                    minimum: 0, // No consideraremos ids negativas
                    description: "The student_id field must be a positive int."
                },
                scores: {
                    bsonType: "array",
                    minItems: 1,
                    maxItems: 50000, // Consideramos que más de esta cantidad de transacciones excedería el tamaño máximo de un documento (16MB)
                    items: {
                        bsonType: "object",
                        required: ["type", "score"],
                        properties: {
                          type: {
                            bsonType: "string",
                            enum: ["exam", "quiz", "homework"],
                            description: "The type field must be a string and can only be one of the given enum values."
                          },
                          score: {
                            bsonType: "double",
                            minimum: 0, // No consideraremos puntajes negativos
                            maximum: 100, // El puntaje más alto es 100
                            description: "The student_id field must be a positive int."
                          }
                        }
                    },
                    uniqueItems: true,
                    description: "The scores field must be an array."
                },
                class_id: {
                    bsonType: "int",
                    minimum: 0, // No consideraremos ids negativas
                    description: "The student_id field must be a positive int."
                }
            },
        }
    },
    validationLevel: "strict",
    validationAction: "error",
});

