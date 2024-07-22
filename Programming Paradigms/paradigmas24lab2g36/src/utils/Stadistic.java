package utils;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import namedEntities.NamedEntity;

public class Stadistic {
    public static void computeCatStats(List<NamedEntity> Entities) {
        HashMap<String, List<NamedEntity>> Categories = new HashMap<String, List<NamedEntity>>();
        String Category;
        for (NamedEntity entity : Entities) {
            Category = entity.getCategory().get_Category_id();
            if (Categories.containsKey(Category)) {
                Categories.get(Category).add(entity);
            } else {
                List<NamedEntity> list = new ArrayList<NamedEntity>();
                list.add(entity);
                Categories.put(Category, list);
            }
        }

        printStats(Categories, "Category");
    }

    public static void computeTopicStats(List<NamedEntity> Entities) {
        HashMap<String, List<NamedEntity>> Topics = new HashMap<String, List<NamedEntity>>();
        List<String> Topic;
        for (NamedEntity entity : Entities) {
            Topic = entity.getTopics();
            for (String topic : Topic) {
                if (Topics.containsKey(topic)) {
                    Topics.get(topic).add(entity);
                } else {
                    List<NamedEntity> list = new ArrayList<NamedEntity>();
                    list.add(entity);
                    Topics.put(topic, list);
                }
            }
        }

        printStats(Topics, "Topic");
    }

    private static void printStats(HashMap<String, List<NamedEntity>> Specimens, String selection) {
        for (Map.Entry<String, List<NamedEntity>> entry : Specimens.entrySet()) {
            System.out.println(selection + ": " + entry.getKey());

            for (NamedEntity entity : entry.getValue()) {
                System.out.print(" ".repeat(selection.length() + 2));
                System.out.println(entity.getName() + " (" + entity.getCounter() + ")");
            }
        }
    }
}
