package app;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.sql.SparkSession;

import app.utils.Config;
import app.feed.FeedsData;
import app.utils.UserInterface;

public class NamedEntitiesCount {

    public static void main(String[] args) {
        SparkSession spark = SparkSession
            .builder()
            .appName("NamedEntitiesCount")
            .getOrCreate();

        JavaSparkContext sc = new JavaSparkContext(spark.sparkContext());        

        UserInterface ui = new UserInterface();
        Config config = ui.handleInput(args);

        run(config, ui, sc);

        spark.stop();
    }

    private static void run(Config config, UserInterface ui, JavaSparkContext sc) {
        if (config.getPrintHelp()) {
            UserInterface.printHelp();
            return;
        }

        ui.processFeedParameters(config);
        
        if (config.getPrintFeed() || !config.getComputeNamedEntities()) {
            FeedsData.printFeeds();
        }

        if (config.getComputeNamedEntities()) {
            ui.computeStats(config, sc);
        }
    }
}
