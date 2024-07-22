package app.utils;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.apache.spark.api.java.JavaSparkContext;

import java.io.File;
import java.nio.file.Files;
import java.io.FileWriter;
import java.nio.file.Paths;

import app.feed.*;
import app.namedEntities.NamedEntity;
import app.namedEntities.heuristics.*;

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

    private static Config setDefaultConfig(){
        return new Config(true, false, false, null, null, null);
    }

    public Config handleInput(String[] args) {
        if (args.length == 0) {
            return setDefaultConfig();
        }
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
                            return setDefaultConfig();
                        }
                    }
                    if (option.getAppearances() > 1) {
                        System.out.println("Repeated option " + option.getName());
                        return setDefaultConfig();
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
                        return setDefaultConfig();
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

    public static void printHelp() {
        DirectoryPaths p = new DirectoryPaths();
        List<FeedsData> feedsDataArray = FeedsData.getFeeds(p.getDataPath());
        LinkedHashMap<String, String> heuristics = Heuristic.getHeuristics(p.getDataPath());
        System.out.println("Usage:"); 
        System.out.println("  To run local:                        ./run-local.sh [SPARK_OPTIONS] -- [APP_OPTIONS]");
        System.out.println("APP_OPTIONS:");
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
        System.out.println("SPARK_OPTIONS:");
        System.out.println("  --master MASTER_URL                  spark://host:port, mesos://host:port, yarn,");
        System.out.println("                                       k8s://https://host:port, or local (Default: local[*]).");
        System.out.println("  --deploy-mode DEPLOY_MODE            Whether to launch the driver program locally (\"client\") or");
        System.out.println("                                       on one of the worker machines inside the cluster (\"cluster\")");
        System.out.println("                                       (Default: client).");
        System.out.println("  --class CLASS_NAME                   Your application's main class (for Java / Scala apps).");
        System.out.println("  --name NAME                          A name of your application.");
        System.out.println("  --jars JARS                          Comma-separated list of local jars to include on the driver");
        System.out.println("                                       and executor classpaths.");
        System.out.println("  --packages                           Comma-separated list of maven coordinates of jars to include");
        System.out.println("                                       on the driver and executor classpaths. Will search the local");
        System.out.println("                                       maven repo, then maven central and any additional repositories");
        System.out.println("                                       specified through --repositories. The format for the coordinates");
        System.out.println("                                       should be groupId:artifactId:version.");
        System.out.println("  --exclude-packages                   Comma-separated list of groupId:artifactId, to exclude while");
        System.out.println("                                       resolving the dependencies provided in --packages to avoid");
        System.out.println("                                       dependency conflicts.");
        System.out.println("  --repositories                       Comma-separated list of additional remote repositories to search");
        System.out.println("                                       for the maven coordinates given with --packages.");
        System.out.println("  --py-files PY_FILES                  Comma-separated list of .zip, .egg, or .py files to place on");
        System.out.println("                                       the PYTHONPATH for Python apps.");
        System.out.println("  --files FILES                        Comma-separated list of files to be placed in the working");
        System.out.println("                                       directory of each executor. File paths of these files have to");
        System.out.println("                                       be absolute or be in the DFS if running on a cluster.");
        System.out.println("  --archives ARCHIVES                  Comma-separated list of archives to be extracted into the");
        System.out.println("                                       working directory of each executor.\n");
        System.out.println("  --conf, -c PROP=VALUE                Arbitrary Spark configuration property.");
        System.out.println("  --properties-file FILE               Path to a file from which to load extra properties. If not");
        System.out.println("                                       specified, this will look for conf/spark-defaults.conf\n");
        System.out.println("  --driver-memory MEM                  Memory for driver (e.g. 1000M, 2G) (Default: 1024M).");
        System.out.println("  --driver-java-options                Extra Java options to pass to the driver.");
        System.out.println("  --driver-library-path                Extra library path entries to pass to the driver.");
        System.out.println("  --driver-class-path                  Extra class path entries to pass to the driver. Note that");
        System.out.println("                                       jars added with --jars are automatically included in the");
        System.out.println("                                       classpath.\n");
        System.out.println("  --executor-memory MEM                Memory per executor (e.g. 1000M, 2G) (Default: 1G).\n");
        System.out.println("  --proxy-user NAME                    User to impersonate when submitting the application.");
        System.out.println("                                       This argument does not work with --principal / --keytab.\n");
        System.out.println("  --help, -h                           Show this help message and exit.");
        System.out.println("  --verbose, -v                        Print additional debug output.");
        System.out.println("  --version                            Print the version of current Spark.\n");
        System.out.println("Spark Connect only:");
        System.out.println("  --remote CONNECT_URL                 URL to connect to the server for Spark Connect, e.g.,");
        System.out.println("                                       spark://host:port. --master and --deploy-mode cannot be set");
        System.out.println("                                       together with this option. This option is experimental, and");
        System.out.println("                                       might change between minor releases.\n");
        System.out.println("Cluster deploy mode only:");
        System.out.println("  --driver-cores NUM                   Number of cores used by the driver, only in cluster mode");
        System.out.println("                                       (Default: 1).\n");
        System.out.println("Spark standalone or Mesos with cluster deploy mode only:");
        System.out.println("  --supervise                          If given, restarts the driver on failure.\n");
        System.out.println("Spark standalone, Mesos or K8s with cluster deploy mode only:");
        System.out.println("  --kill SUBMISSION_ID                 If given, kills the driver specified.");
        System.out.println("  --status SUBMISSION_ID               If given, requests the status of the driver specified.\n");
        System.out.println("Spark standalone and Mesos only:");
        System.out.println("  --total-executor-cores NUM           Total cores for all executors.\n");
        System.out.println("Spark standalone, YARN and Kubernetes only:");
        System.out.println("  --executor-cores NUM                 Number of cores per executor. (Default: 1 in YARN and");
        System.out.println("                                       K8S modes, or all available cores on the worker in standalone");
        System.out.println("                                       mode).\n");
        System.out.println("Spark on YARN and Kubernetes only:");
        System.out.println("  --num-executors NUM                  Number of executors to launch (Default: 2).");
        System.out.println("                                       If dynamic allocation is enabled, the initial number of");
        System.out.println("                                       executors will be at least NUM.");
        System.out.println("  --principal PRINCIPAL                Principal to be used to login to KDC.");
        System.out.println("  --keytab KEYTAB                      The full path to the file that contains the keytab for the");
        System.out.println("                                       principal specified above.");
        System.out.println("Spark on YARN only:");
        System.out.println("  --queue QUEUE_NAME                   The YARN queue to submit to (Default: \"default\").\n");
    }

    private static void failHandler(Config config) {
        printHelp();
        config = setDefaultConfig();
    }

    public void processFeedParameters(Config config) {
        DirectoryPaths p = new DirectoryPaths();
        FeedsData.getFeeds(p.getDataPath()); //Obtiene los feeds y los inicializa de ser necesario
        if (config.getFeedKey() != null) {
            try {
                FeedsData.processFeeds(config.getFeedKey().split(" "));
            } catch (IllegalArgumentException e) {
                System.err.println(e.getMessage());
                failHandler(config);
            }
        }
    }

    private static void storeBigData(List<List<Article>> allArticles) {
        String content = "";

        for (List<Article> articles : allArticles) {
            content = content + Article.ArticlestoText(articles) + "\n";
        }

        DirectoryPaths p = new DirectoryPaths();
        File file = new File(p.getDataPath() + "/bigData.txt");

        try {
            FileWriter writer = new FileWriter(file);
            writer.write(content);
            writer.close();
        } catch (IOException e) {
            System.err.println("Error al escribir en el archivo: " + e.getMessage());
        }
    }

    private static List<String> getCandidates(Config config, JavaSparkContext sc) {
        List<List<Article>> articles = null;
        try {
            articles = FeedsData.getArticles();
        } catch (NullPointerException e) {
            System.err.println("Error al obtener los artículos: " + e.getMessage());
        }
        storeBigData(articles);

        // Leer el contenido del archivo como un String
        String text = "";
        DirectoryPaths p = new DirectoryPaths();
        try {
            text = new String(Files.readAllBytes(Paths.get(p.getDataPath() + "/bigData.txt")));
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        }

        List<String> candidates = new ArrayList<String>();

        LinkedHashMap<String, String> heuristics = Heuristic.getHeuristics(p.getDataPath());
        Heuristic heuristic;
        switch (config.getHeuristicKey()) {
            case "CapWord":
                heuristic = new CapitalizedWordHeuristic("CapWord", heuristics.get("CapWord"));
                break;

            case "NoDot":
                heuristic = new NoPrefixDotCapHeuristic("NoDot", heuristics.get("NoDot"));
                break;

            case "FilterCP":
                heuristic = new FiltredCapHeuristic("FilterCP", heuristics.get("FilterCP"));
                break;

            default:
                System.out.println(config.getHeuristicKey() + " is an invalid heuristic name");
                return null;
        }

        candidates = heuristic.Extraction(text, sc);
        return candidates;
    }
    
    public void computeStats(Config config, JavaSparkContext sc){
        List<NamedEntity> dictEntities = new ArrayList<NamedEntity>();
        DirectoryPaths p = new DirectoryPaths();
        try {
            dictEntities = JSONParser.parseJsonDictionayData(p.getDataPath() + "/dictionary.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        List<String> candidates = getCandidates(config, sc);
        if (candidates == null) {
            failHandler(config);                                                            
        }
        List<NamedEntity> entities = Heuristic.Classification(dictEntities, candidates, sc);
        if (entities == null) {
            failHandler(config);
        }

        System.out.println("Computing named entities using " + config.getHeuristicKey() + '\n');
        System.out.println("Stats: ");
        System.out.println("-".repeat(80));

        String statKey = (config.getStatKey() == null) ? "cat" : config.getStatKey();
        switch (statKey) {
            case "topic":
                Stadistic.computeTopicStats(entities);
                break;

            case "cat":
                Stadistic.computeCatStats(entities);
                break;

            default:
                System.out.println(statKey + " is not a valid stat format");
                failHandler(config);
            }
    }
}
