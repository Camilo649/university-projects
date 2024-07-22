package utils;

public class Config {
    private boolean printHelp;
    private boolean printFeed;
    private boolean computeNamedEntities;
    private String feedKey;
    private String heuristicsKey;
    private String statKey;

    public Config(boolean printHelp, boolean printFeed, boolean computeNamedEntities,
            String feedKey, String heuristic, String statKey) {
        this.printHelp = printHelp;
        this.printFeed = printFeed;
        this.computeNamedEntities = computeNamedEntities;
        this.feedKey = feedKey;
        this.heuristicsKey = heuristic;
        this.statKey = statKey;
    }

    public boolean getPrintHelp() {
        return printHelp;
    }

    public boolean getPrintFeed() {
        return printFeed;
    }

    public boolean getComputeNamedEntities() {
        return computeNamedEntities;
    }

    public String getFeedKey() {
        return feedKey;
    }

    public String getHeuristicKey() {
        return heuristicsKey;
    }

    public String getStatKey() {
        return statKey;
    }
}
