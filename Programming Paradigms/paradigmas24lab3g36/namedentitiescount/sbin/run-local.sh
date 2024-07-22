#!/bin/bash

# Directorio de la aplicación
JAR_PATH="$APP_HOME/namedentitiescount/target/NamedEntitiesCount-1.0-SNAPSHOT.jar"

# Argumentos de Spark
SPARK_OPTS=(
  --master local[2]
)

# Argumentos específicos de la aplicación
APP_OPTS=()

# Separar los argumentos de Spark y los de la aplicación
SPARK_ARG_FLAG=0

for arg in "$@"; do
  if [ $SPARK_ARG_FLAG -eq 1 ]; then
    APP_OPTS+=("$arg")
  else
    SPARK_OPTS+=("$arg")
  fi

  if [ "$arg" == "--" ]; then
    SPARK_ARG_FLAG=1
    SPARK_OPTS=("${SPARK_OPTS[@]::${#SPARK_OPTS[@]}-1}")  # Remove "--" from SPARK_OPTS
  fi
done

# Corre la aplicación con spark-submit
echo ""
echo "Running application..."
"${SPARK_HOME}/bin/spark-submit" \
  "${SPARK_OPTS[@]}" \
  "$JAR_PATH" \
  "${APP_OPTS[@]}" 2>/dev/null
