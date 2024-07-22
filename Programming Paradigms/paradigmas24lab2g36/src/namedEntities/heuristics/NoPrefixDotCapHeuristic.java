package namedEntities.heuristics;

import java.util.List;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.text.Normalizer;

public final class NoPrefixDotCapHeuristic extends Heuristic {

    public NoPrefixDotCapHeuristic(String Heuristic_identifier, String Description) {
        super(Heuristic_identifier, Description);
    }

    public List<String> Extraction(String text) {
        List<String> candidates = new ArrayList<>();

        text = text.replaceAll("[-+^:,\"]", "");
        text = Normalizer.normalize(text, Normalizer.Form.NFD);
        text = text.replaceAll("\\p{M}", "");

        Pattern pattern = Pattern.compile("(?<!\\.)(?<!\\.\\s)[A-Z][a-z]+(?:\\s[A-Z][a-z]+)*");

        Matcher matcher = pattern.matcher(text);

        while (matcher.find()) {
            candidates.add(matcher.group());
        }
        return candidates;
    }
}