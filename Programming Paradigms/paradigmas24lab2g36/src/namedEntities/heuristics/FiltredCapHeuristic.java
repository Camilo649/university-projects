package namedEntities.heuristics;

import java.util.List;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.IOException;
import java.text.Normalizer;
import utils.JSONParser;

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

    public FiltredCapHeuristic(String Heuristic_identifier, String Description) {
        super(Heuristic_identifier, Description);
    }

    public List<String> Extraction(String text) {
        List<String> candidates = new ArrayList<>();

        text = text.replaceAll("[-+.^:,\"]", "");
        text = Normalizer.normalize(text, Normalizer.Form.NFD);
        text = text.replaceAll("\\p{M}", "");

        Pattern pattern = Pattern.compile("[A-Z][a-z]+(?:\\s[A-Z][a-z]+)*");

        Matcher matcher = pattern.matcher(text);

        String[] filterWords = new String[0];
        try {
            filterWords = JSONParser.parseJsonWordsToFilter("src/data/filterDictionary.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        int i, n = filterWords.length;
        boolean filter;
        String candidate;
        while (matcher.find()) {
            i = 0;
            filter = false;
            candidate = matcher.group().trim();

            while (!filter && i < n) {
                if (filterWords[i].equals(candidate)) {
                    filter = true;
                }
                i++;
            }

            if (!filter) {
                candidates.add(candidate);
            }
        }

        return candidates;
    }
}
