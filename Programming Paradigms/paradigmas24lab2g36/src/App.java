import java.io.IOException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.LinkedHashMap;

import feed.Article;
import feed.FeedParser;
import namedEntities.NamedEntity;
import utils.Config;
import utils.FeedsData;
import utils.JSONParser;
import utils.UserInterface;
import utils.Stadistic;
import namedEntities.heuristics.*;

public class App {

    public static void main(String[] args) {

        List<FeedsData> feedsDataArray = new ArrayList<>();
        try {
            feedsDataArray = JSONParser.parseJsonFeedsData("src/data/feeds.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        LinkedHashMap<String, String> heuristics = new LinkedHashMap<String, String>();
        try {
            heuristics = JSONParser.parseJsonHeuristics("src/data/heuristics.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        UserInterface ui = new UserInterface();
        Config config = ui.handleInput(args);

        run(config, feedsDataArray, heuristics);
    }

    private static void run(Config config, List<FeedsData> feedsDataArray, LinkedHashMap<String, String> heuristics) {

        if (feedsDataArray == null || feedsDataArray.size() == 0) {
            System.out.println("No feeds data found");
            return;
        }

        if (config.getPrintHelp()) {
            UserInterface.printHelp(feedsDataArray, heuristics);
            return;
        }

        if (config.getFeedKey() != null) {
            String[] parametros = config.getFeedKey().split(" ");
            List<FeedsData> feeds = new ArrayList<FeedsData>();
            for (String parametro : parametros) {
                for (int i = 0; i < feedsDataArray.size(); i++) {
                    FeedsData feed = feedsDataArray.get(i);
                    if (feed.getLabel().equals(parametro)) {
                        feeds.add(new FeedsData(feed.getLabel(), feed.getUrl(), feed.getType()));
                        break;
                    }
                    if (i == feedsDataArray.size() - 1) {
                        System.out.println(parametro + " is not a feed name");
                        UserInterface.printHelp(feedsDataArray, heuristics);
                        return;
                    }
                }
            }
            feedsDataArray = feeds;
        }

        List<List<Article>> feeds = new ArrayList<List<Article>>();

        for (FeedsData feed : feedsDataArray) {
            try {
                String XMLString = FeedParser.fetchFeed(feed.getUrl());
                feeds.add(new ArrayList<Article>(FeedParser.parseXML(XMLString)));
            } catch (MalformedURLException e) {
                System.out.println("-".repeat(80));
                feed.print();
                System.out.println(e.getMessage());
                System.out.println("-".repeat(80) + "\n");
            } catch (IOException e) {
                System.out.println("-".repeat(80));
                feed.print();
                System.out.println(e.getMessage());
                System.out.println("-".repeat(80) + "\n");
            } catch (Exception e) {
                System.out.println("-".repeat(80));
                feed.print();
                System.out.println(e.getMessage());
                System.out.println("-".repeat(80) + "\n");
            }
        }

        if (config.getPrintFeed() || !config.getComputeNamedEntities()) {
            for (List<Article> AllArticles : feeds) {
                for (Article article : AllArticles) { // for each article
                    article.print();
                }
                System.out.println("\n");
            }
        }

        if (config.getComputeNamedEntities()) {

            System.out.println("Computing named entities using " + config.getHeuristicKey());

            List<NamedEntity> dictEntities = new ArrayList<NamedEntity>();
            try {
                dictEntities = JSONParser.parseJsonDictionayData("src/data/dictionary.json");
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

            String text = "";
            for (List<Article> feed : feeds) {
                text = text + Article.ArticlestoText(feed);
            }
            List<String> candidates = new ArrayList<String>();

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
                    UserInterface.printHelp(feedsDataArray, heuristics);
                    return;
            }

            candidates = heuristic.Extraction(text);

            List<NamedEntity> entities = Heuristic.Classification(dictEntities, candidates);

            System.out.println("\nStats: ");
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
                    System.out.println(statKey + " is no a valid stat format");
                    UserInterface.printHelp(feedsDataArray, heuristics);
                    return;
            }
        }
    }
}
