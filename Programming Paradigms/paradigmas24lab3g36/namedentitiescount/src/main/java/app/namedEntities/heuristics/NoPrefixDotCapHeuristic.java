package app.namedEntities.heuristics;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.FlatMapFunction;

import java.text.Normalizer;

public final class NoPrefixDotCapHeuristic extends Heuristic {
    private static final Pattern pattern = Pattern.compile("[A-Z][a-z]+(?:\\s[A-Z][a-z]+)*");

    public NoPrefixDotCapHeuristic(String Heuristic_identifier, String Description) {
        super(Heuristic_identifier, Description);
    }

    public List<String> Extraction(String text, JavaSparkContext sc) {
        text = text.replaceAll("[-+^:;,\"|/\''¡!¿?]", "");
        text = Normalizer.normalize(text, Normalizer.Form.NFD);
        text = text.replaceAll("\\p{M}", "");

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

        List<String> candidates = candidatesRDD.collect();
        return candidates;
    }
}