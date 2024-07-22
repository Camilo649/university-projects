package app.namedEntities.heuristics;

import java.util.List;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaPairRDD;
import scala.Tuple2;

import java.io.IOException;
import java.text.Normalizer;
import java.util.ArrayList;
import java.util.LinkedHashMap;

import app.namedEntities.*;
import app.namedEntities.categories.*;
import app.utils.JSONParser;

public abstract class Heuristic {
    private String Heuristic_identifier;
    private String Description;
    private static LinkedHashMap<String, String> heuristics = null;

    public Heuristic(String Heuristic_identifier, String Description) {
        this.Heuristic_identifier = Heuristic_identifier;
        this.Description = Description;
    }

    public String get_Heuristic_id() {
        return Heuristic_identifier;
    }

    public String get_Description() {
        return Description;
    }

    public static LinkedHashMap<String, String> getHeuristics(String dataPath) {
        if (heuristics == null) {
            heuristics = new LinkedHashMap<String, String>();
            try {
                heuristics = JSONParser.parseJsonHeuristics(dataPath + "/heuristics.json");
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

            if (heuristics == null || heuristics.size() == 0) {
                System.out.println("No heuristics data found");
            }
        }
        return heuristics;
    }

    public void print() {
        System.out.println("Heuristic: " + Heuristic_identifier);
        System.out.println("Description: " + Description);
    }

    protected static String Normalize(String text) {
        text = text.replaceAll("[-+.^:;,\"|\'¡!¿?]", "");
        text = Normalizer.normalize(text, Normalizer.Form.NFD);
        text = text.replaceAll("\\p{M}", "");

        return text;
    }

    public static List<NamedEntity> Classification(List<NamedEntity> DictionaryEntitites, List<String> Candidates, JavaSparkContext sc) {
        JavaRDD<String> candidatesRDD = sc.parallelize(Candidates);
        
        JavaPairRDD<String, NamedEntity> entityPairsRDD = candidatesRDD.mapToPair(candidate -> {
            for (NamedEntity dictEntity : DictionaryEntitites) {
                List<String> Keywords = dictEntity.getKeywords();
                for (String key : Keywords) {
                    if (key.equals(candidate)) {
                        return new Tuple2<>(dictEntity.getName(), dictEntity);
                    }
                }
            }
            // Si el candidato no aparece en el diccionario, se guarda como OTHER
            Category DefaultCategory = new OTHER();
            List<String> DefaultTopic = new ArrayList<>();
            DefaultTopic.add("OTHER");
            return new Tuple2<>(candidate, (new NamedEntity(candidate, DefaultCategory, DefaultTopic, null)));
        });
    
        JavaPairRDD<String, NamedEntity> reducedEntityPairsRDD = entityPairsRDD.reduceByKey((entity1, entity2) -> {
            // Crear una nueva instancia de NamedEntity con el contador actualizado
            NamedEntity combinedEntity = new NamedEntity(entity1.getName(), entity1.getCategory(), entity1.getTopics(), entity1.getKeywords());
            combinedEntity.setCounter(entity1.getCounter() + entity2.getCounter());
            return combinedEntity;
        });

        return reducedEntityPairsRDD.map(Tuple2::_2).collect();
    }

    public abstract List<String> Extraction(String text, JavaSparkContext sc);
}
