package app.utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedHashMap;

import org.json.JSONArray;
import org.json.JSONObject;

import app.namedEntities.*;
import app.namedEntities.categories.*;
import app.feed.FeedsData;

public class JSONParser {

    static public List<FeedsData> parseJsonFeedsData(String jsonFilePath) throws IOException {
        String jsonData = new String(Files.readAllBytes(Paths.get(jsonFilePath)));
        List<FeedsData> feedsList = new ArrayList<>();

        JSONArray jsonArray = new JSONArray(jsonData);
        for (int i = 0; i < jsonArray.length(); i++) {
            JSONObject jsonObject = jsonArray.getJSONObject(i);
            String label = jsonObject.getString("label");
            String url = jsonObject.getString("url");
            String type = jsonObject.getString("type");
            feedsList.add(new FeedsData(label, url, type));
        }
        return feedsList;
    }

    static public List<NamedEntity> parseJsonDictionayData(String jsonFilePath) throws IOException {
        String jsonData = new String(Files.readAllBytes(Paths.get(jsonFilePath)));
        List<NamedEntity> namedEntitiesList = new ArrayList<>();

        JSONArray jsonArray = new JSONArray(jsonData);
        for (int i = 0; i < jsonArray.length(); i++) {
            JSONObject jsonObject = jsonArray.getJSONObject(i);
            String label = jsonObject.getString("label");
            String Category_key = jsonObject.getString("Category");

            JSONArray Topics = jsonObject.getJSONArray("Topics");
            List<String> topics = new ArrayList<String>();
            for (int j = 0; j < Topics.length(); j++) {
                topics.add(Topics.getString(j));
            }

            JSONArray keyWords = jsonObject.getJSONArray("keywords");
            List<String> keywords = new ArrayList<String>();
            for (int j = 0; j < keyWords.length(); j++) {
                keywords.add(keyWords.getString(j));
            }

            Category Category;
            switch (Category_key) {
                case "PERSON":
                    Category = new PERSON();
                    break;

                case "LOCATION":
                    Category = new LOCATION();
                    break;

                case "ORGANIZATION":
                    Category = new ORGANIZATION();
                    break;

                default:
                    Category = new OTHER();
            }

            namedEntitiesList.add(new NamedEntity(label, Category, topics, keywords));
        }
        return namedEntitiesList;
    }

    static public LinkedHashMap<String, String> parseJsonHeuristics(String jsonFilePath) throws IOException {
        String jsonData = new String(Files.readAllBytes(Paths.get(jsonFilePath)));
        LinkedHashMap<String, String> heuristics = new LinkedHashMap<>();

        JSONArray jsonArray = new JSONArray(jsonData);
        for (int i = 0; i < jsonArray.length(); i++) {
            JSONObject jsonObject = jsonArray.getJSONObject(i);
            String key = jsonObject.getString("keyname");
            String value = jsonObject.getString("description");
            heuristics.put(key, value);
        }
        return heuristics;
    }

    static public String[] parseJsonWordsToFilter(String jsonFilePath) throws IOException {
        String jsonData = new String(Files.readAllBytes(Paths.get(jsonFilePath)));
        JSONObject jsonObject = new JSONObject(jsonData);
        JSONArray jsonArray = jsonObject.getJSONArray("words");

        String[] words = new String[jsonArray.length()];
        for (int i = 0; i < jsonArray.length(); i++) {
            words[i] = jsonArray.getString(i);
        }
        return words;
    }
}
