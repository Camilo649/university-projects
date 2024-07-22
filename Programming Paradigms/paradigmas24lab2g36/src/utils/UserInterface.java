package utils;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class UserInterface {

    private HashMap<String, String> optionDict;

    private List<Option> options;

    public UserInterface() {
        options = new ArrayList<Option>();
        options.add(new Option("-h", "--help", 0));
        options.add(new Option("-f", "--feed", 1));
        options.add(new Option("-ne", "--named-entity", 1));
        options.add(new Option("-pf", "--print-feed", 0));
        options.add(new Option("-sf", "--stats-format", 1));

        optionDict = new HashMap<String, String>();
    }

    public Config handleInput(String[] args) {

        Integer i = 0;
        while (i < args.length) {
            for (Option option : options) {
                if (i == args.length) {
                    break;
                }
                if (option.getName().equals(args[i]) || option.getLongName().equals(args[i])) {
                    option.incAppearances();
                    if (option.getnumValues() == 0) {
                        optionDict.put(option.getName(), null);
                        i++;
                    } else {
                        if (i + 1 < args.length && !args[i + 1].startsWith("-")) {
                            String parametros = args[i + 1];
                            i++;
                            if (option.getName().equals("-f") || option.getLongName().equals("--feed")) {
                                while (i + 1 < args.length && !args[i + 1].startsWith("-")) {
                                    parametros += " " + args[i + 1];
                                    option.inc_numValues();
                                    i++;
                                }
                                optionDict.put("-f", parametros);
                            } else {
                                optionDict.put(option.getName(), parametros);
                            }
                            i++;
                        } else {
                            System.out.println("Invalid inputs");
                            return new Config(true, false, false, null, null, null);
                        }
                    }
                    if (option.getAppearances() > 1) {
                        System.out.println("Repeated option " + option.getName());
                        return new Config(true, false, false, null, null, null);
                    }
                } else {
                    Boolean coincidence = false;
                    for (Option flag : options) {
                        if (flag.getName().equals(args[i]) || flag.getLongName().equals(args[i])) {
                            coincidence = true;
                            break;
                        }
                    }
                    if (!coincidence) {
                        System.out.println(args[i] + " is not a valid option");
                        return new Config(true, false, false, null, null, null);
                    }
                }
            }
        }

        Boolean printHelp = optionDict.containsKey("-h");
        Boolean printFeed = optionDict.containsKey("-pf");
        Boolean computeNamedEntities = optionDict.containsKey("-ne");
        String heuristicKey;
        String statKey = optionDict.get("-sf");
        heuristicKey = computeNamedEntities ? optionDict.get("-ne") : null;

        String feedKey = optionDict.get("-f");

        return new Config(printHelp, printFeed, computeNamedEntities, feedKey, heuristicKey, statKey);
    }

    public static void printHelp(List<FeedsData> feedsDataArray, LinkedHashMap<String, String> heuristics) {
        System.out.println("Usage: make run ARGS=\"[OPTION]\"");
        System.out.println("Options:");
        System.out.println("  -h, --help:                          Show this help message and exit");
        System.out.println("  -f, --feed <feedKey>:                Fetch and process the feed with");
        System.out.println("                                       the specified key");
        System.out.println("                                       Available feed keys are: ");
        for (FeedsData feedData : feedsDataArray) {
            System.out.println("                                       " + feedData.getLabel());
        }
        System.out.println("  -ne, --named-entity <heuristicName>: Use the specified heuristic to extract");
        System.out.println("                                       named entities");
        System.out.println("                                       Available heuristic names are: ");
        for (Map.Entry<String, String> entry : heuristics.entrySet()) {
            System.out.println(
                    "                                       " + entry.getKey() + " (" + entry.getValue() + ")");
        }
        System.out.println("                                       <name>: <description>");
        System.out.println("  -pf, --print-feed:                   Print the fetched feed");
        System.out.println("  -sf, --stats-format <format>:        Print the stats in the specified format");
        System.out.println("                                       Available formats are: ");
        System.out.println("                                       cat: Category-wise stats");
        System.out.println("                                       topic: Topic-wise stats");
    }
}
