package namedEntities.heuristics;

import java.util.List;
import java.util.ArrayList;
import namedEntities.*;
import namedEntities.categories.*;

public abstract class Heuristic {
    private String Heuristic_identifier;
    private String Description;

    public Heuristic(String Heuristic_identifier, String Description) {
        this.Heuristic_identifier = Heuristic_identifier;
        this.Description = Description;
    }

    public String get_Heuristic_id() {
        return Heuristic_identifier;
    }

    public String get_Description() {
        return Description;
    }

    public void print() {
        System.out.println("Heuristic: " + Heuristic_identifier);
        System.out.println("Description: " + Description);
    }

    public static List<NamedEntity> Classification(List<NamedEntity> DictionaryEntitites, List<String> Candidates) {
        List<NamedEntity> Entitites = new ArrayList<>();
        Boolean match;
        for (String candidate : Candidates) {
            match = false;
            for (NamedEntity dictEntity : DictionaryEntitites) {
                List<String> Keywords = dictEntity.getKeywords();
                for (String key : Keywords) {
                    if (key.equals(candidate)) {
                        if (Entitites.contains(dictEntity)) {
                            int index = Entitites.indexOf(dictEntity);
                            Entitites.get(index).incrementCounter();
                        } else {
                            Entitites.add(dictEntity);
                        }
                        match = true;
                        break;
                    }
                }
                if (match) {
                    break;
                }
            }
            if (!match) { // If the candidate is not in the dictionary
                for (NamedEntity entity : Entitites) {
                    if (entity.getName().equals(candidate)) {
                        entity.incrementCounter();
                        match = true;
                        break;
                    }
                }
                if (!match) {
                    Category DefaultCategory = new OTHER();
                    List<String> DefaultTopic = new ArrayList<>();
                    DefaultTopic.add("OTHER");
                    Entitites.add(new NamedEntity(candidate, DefaultCategory, DefaultTopic, null));
                }
            }
        }
        return Entitites;
    }

    public abstract List<String> Extraction(String text);
}
