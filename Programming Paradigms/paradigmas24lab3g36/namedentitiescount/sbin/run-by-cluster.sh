#!/bin/bash

# URL del master de Spark
SPARK_MASTER_URL=$1
shift  # Eliminar la URL del master de los argumentos

# Verificar que la URL del master comience con "spark://"
if [[ ! "$SPARK_MASTER_URL" =~ ^spark:// ]]; then
  echo "Error: Invalid master URL."
  print_help
fi

# Argumentos de Spark y de la aplicación
SPARK_OPTS=(
    --master "$SPARK_MASTER_URL"
)
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
    SPARK_OPTS=("${SPARK_OPTS[@]::${#SPARK_OPTS[@]}-1}")  # Eliminar "--" de SPARK_OPTS
  fi
done

# Directorio de la aplicación
JAR_PATH="$APP_HOME/namedentitiescount/target/NamedEntitiesCount-1.0-SNAPSHOT.jar"

# Función para verificar y manejar los workers
check_and_handle_workers() {
  # Verificar el número de workers activos
  WORKERS_RUNNING=$(jps | grep Worker | wc -l)
  if [ "$WORKERS_RUNNING" -eq 0 ]; then
    start_workers
  elif [ "$WORKERS_RUNNING" -ne 2 ]; then
    echo "Unexpected number of Spark workers ($WORKERS_RUNNING). Cleaning up and starting new workers..."
    cleanup_workers
    echo ""
    start_workers
  fi
  run_application
}

# Función para iniciar los workers
start_workers() {
  echo "Starting Spark workers..."

 # Eliminar el archivo spark-env.sh si existe
 if [ -f "${SPARK_HOME}/conf/spark-env.sh" ]; then
  rm "${SPARK_HOME}/conf/spark-env.sh"
  if [ $? -ne 0 ]; then
    echo "Failed to remove ${SPARK_HOME}/conf/spark-env.sh. Exiting..."
    print_help
  fi
 fi

  "${SPARK_HOME}/sbin/start-worker.sh" "$SPARK_MASTER_URL" >/dev/null &
  pid1=$!

  "${SPARK_HOME}/sbin/start-worker.sh" "$SPARK_MASTER_URL" >/dev/null &
  pid2=$!

  # Esperar a que ambos workers se inicien
  wait $pid1 >/dev/null
  wait $pid2 >/dev/null

  echo "Spark workers started."
  echo ""

  # Esperar unos segundos para asegurar que los workers están en ejecución
  sleep 5
}

# Función para limpiar los workers existentes
cleanup_workers() {
  # Obtener los PID de los workers de Spark
  WORKER_PIDS=$(jps | grep Worker | awk '{print $1}')
  
  if [ -z "$WORKER_PIDS" ]; then
    echo "No Spark workers to clean up."
  else
    # Detener cada worker usando su PID
    for pid in $WORKER_PIDS; do
      kill "$pid"
    done

    # Esperar a que los workers se detengan completamente
    sleep 5

    # Verificar que los workers se hayan detenido
    WORKERS_RUNNING=$(jps | grep Worker | wc -l)
    if [ "$WORKERS_RUNNING" -ne 0 ]; then
      echo "Failed to stop existing Spark workers. Exiting..."
      print_help
    fi
  fi
}

# Correr la aplicación con spark-submit
run_application() {
  echo "Running application..."
  echo ""
  "${SPARK_HOME}/bin/spark-submit" \
    "${SPARK_OPTS[@]}" \
    "$JAR_PATH" \
    "${APP_OPTS[@]}" 2>/dev/null

  if [ $? -ne 0 ]; then
    echo "Failed to run the application with spark-submit."
    print_help
  fi
}

# Mostrar mensaje de ayuda
print_help() {
  SPARK_OPTS=(
  --master local[1]
  )

  APP_OPTS=(
    -h
  )

  "${SPARK_HOME}/bin/spark-submit" \
  "${SPARK_OPTS[@]}" \
  "$JAR_PATH" \
  "${APP_OPTS[@]}" 2>/dev/null
  exit 1
}

echo ""
check_and_handle_workers

