package namedEntities;

import java.util.ArrayList;
import java.util.List;
import namedEntities.categories.Category;

public class NamedEntity {
    private String Name;
    private Category Category;
    private List<String> Topics;
    private List<String> KeyWords;
    private int counter;

    public NamedEntity(String Name, Category Category, List<String> Topics, List<String> KeyWords) {
        this.Name = Name;
        this.Category = Category;
        this.Topics = Topics;
        this.KeyWords = KeyWords;
        this.counter = 1;
    }

    public void incrementCounter() {
        this.counter++;
    }

    public void setCategory(Category Category) {
        this.Category = Category;
    }

    public void addTopics(String Topic) {
        this.Topics.add(Topic);
    }

    public void addKeyWord(String KeyWord) {
        this.KeyWords.add(KeyWord);
    }

    public String getName() {
        return Name;
    }

    public Category getCategory() {
        return Category;
    }

    public List<String> getTopics() {
        return Topics;
    }

    public List<String> getKeywords() {
        return KeyWords;
    }

    public int getCounter() {
        return counter;
    }

    public void print() {
        System.out.println("label: " + Name);
        System.out.println("Category: " + Category.get_Category_id());
        System.out.println("Topics: " + Topics);
        System.out.println("KeyWord: " + KeyWords);
    }
}