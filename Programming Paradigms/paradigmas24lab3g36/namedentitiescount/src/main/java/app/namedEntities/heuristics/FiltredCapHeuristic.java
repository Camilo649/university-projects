package app.namedEntities.heuristics;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Set;
import java.util.HashSet;
import java.io.IOException;

import app.utils.JSONParser;
import app.utils.DirectoryPaths;

import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.FlatMapFunction;

/* 
La motivación de esta heurística fue filtrar en mayor medida las entidades nombradas
obtenidas por la heurística original. Para lograrlo utiliza una lista de "palabras que
comúnmente pueden seguir después de un punto en el español" la cual fue construída
considerando conectores, conjunciones, preposiciones, adverbios locuciones y otros verbos
utilizados para ordenar un texto. 
Para las palabras con tilde, se encuentra también su versión sin tilde. Esto es así, a
pesar que la heurística proveída por la cátedra formatea el código haciendo que no
aparezcan caracteres con estas características, para brindar una mayor generalidad. 
Utilizamos inteligencia artifical como ChatGPT y Copilot para agregar palabras extras.
*/

public final class FiltredCapHeuristic extends Heuristic {
    private static final Pattern pattern = Pattern.compile("[A-Z][a-z]+(?:\\s[A-Z][a-z]+)*");

    public FiltredCapHeuristic(String Heuristic_identifier, String Description) {
        super(Heuristic_identifier, Description);
    }

    public List<String> Extraction(String text, JavaSparkContext sc) {
        text = Normalize(text);
        
        List<String> lines = Arrays.asList(text.split("\n"));
        JavaRDD<String> linesRDD = sc.parallelize(lines);
            
        JavaRDD<String> candidatesRDD = linesRDD.flatMap((FlatMapFunction<String, String>) line -> {
            List<String> candidates = new ArrayList<>();
            Matcher matcher = pattern.matcher(line);

            while (matcher.find()) {
                candidates.add(matcher.group());
            }
            return candidates.iterator();
        });

        DirectoryPaths p = new DirectoryPaths();
        Set<String> filterWords = new HashSet<String>();
            try {
                // Convertimos el arreglo a un Set para mejorar la eficiencia de la búsqueda
                filterWords.addAll(Arrays.asList(JSONParser.parseJsonWordsToFilter(p.getDataPath() + "/filterDictionary.json")));
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

        candidatesRDD = candidatesRDD.filter(word -> !filterWords.contains(word));

        return candidatesRDD.collect();
    }
}
