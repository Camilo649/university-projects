package app.feed;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.List;

import app.utils.JSONParser;

public class FeedsData {
    private String label;
    private String url;
    private String type;
    private static List<FeedsData> feedsDataArray = null;
    private static List<List<Article>> articles = null;

    public FeedsData(String label, String url, String type) {
        this.label = label;
        this.url = url;
        this.type = type;
    }

    public String getLabel() {
        return label;
    }

    public String getUrl() {
        return url;
    }

    public String getType() {
        return type;
    }

    public static List<FeedsData> getFeeds(String dataPath) {
        if(feedsDataArray == null) {
            feedsDataArray = new ArrayList<FeedsData>();
            try {
                feedsDataArray = JSONParser.parseJsonFeedsData(dataPath + "/feeds.json");
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

            if (feedsDataArray == null || feedsDataArray.size() == 0) {
                System.out.println("No feeds data found");
            }
        }
        return feedsDataArray;
    }

    private static List<FeedsData> cloneFeeds() {
        List<FeedsData> feedsDataArrayClone = new ArrayList<FeedsData>();
        for (FeedsData feed : feedsDataArray) {
            feedsDataArrayClone.add(new FeedsData(feed.getLabel(), feed.getUrl(), feed.getType()));
        }
        return feedsDataArrayClone;
    }

    public static void processFeeds(String[] feedKeys) throws IllegalArgumentException {
        List<FeedsData> allFeeds = cloneFeeds();
        feedsDataArray = new ArrayList<FeedsData>();    
        for (String feedKey : feedKeys) {
            for (int i = 0; i < allFeeds.size(); i++) {
                FeedsData feed = allFeeds.get(i);
                if (feed.getLabel().equals(feedKey)) {
                    feedsDataArray.add(new FeedsData(feed.getLabel(), feed.getUrl(), feed.getType()));
                    break;
                }
                if (i == allFeeds.size() - 1) {
                    throw new IllegalArgumentException(feedKey + " is not a feed name");
                }
            }
        }
    }

    public static  List<List<Article>> getArticles() throws NullPointerException {
        if (feedsDataArray == null) {
            throw new NullPointerException("feedsDataArray must not be null when calling this method");
        }
        if (articles == null) {
            articles = new ArrayList<List<Article>>();
            for (FeedsData feed : feedsDataArray) {
                try {
                    String XMLString = FeedParser.fetchFeed(feed.getUrl());
                    articles.add(new ArrayList<Article>(FeedParser.parseXML(XMLString)));
                } catch (MalformedURLException e) {
                    System.out.println("-".repeat(80));
                    feed.printFeed();
                    System.out.println(e.getMessage());
                    System.out.println("-".repeat(80) + "\n");
                } catch (IOException e) {
                    System.out.println("-".repeat(80));
                    feed.printFeed();
                    System.out.println(e.getMessage());
                    System.out.println("-".repeat(80) + "\n");
                } catch (Exception e) {
                    System.out.println("-".repeat(80));
                    feed.printFeed();
                    System.out.println(e.getMessage());
                    System.out.println("-".repeat(80) + "\n");
                }
            }
        }
    
        return articles;
    }

    public void printFeed() {
        System.out.println("Feed: " + label);
        System.out.println("URL: " + url);
        System.out.println("Type: " + type);
    }

    public static void printFeeds() {
        if (articles == null) {
            getArticles(); // Inicializa los artículos de ser necesario
        }
        for (List<Article> AllArticles : articles) {
            for (Article article : AllArticles) {
                article.printArticle();
            }
            System.out.println("\n");
        }
    }
}