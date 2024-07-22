package feed;

import java.util.List;

public class Article {
    private String title;
    private String description;
    private String pubDate;
    private String link;

    // Atributos
    public Article(String title, String description, String pubDate, String link) {
        this.title = title;
        this.description = description;
        this.pubDate = pubDate;
        this.link = link;
    }

    // method 'print'
    public void print() {
        System.out.println("Title: " + (title == null ? "" : title)); // para que no se imprima null sólo
        System.out.println("Description: " + (description == null ? "" : description));
        System.out.println("Publication Date: " + (pubDate == null ? "" : pubDate));
        System.out.println("Link: " + (link == null ? "" : link));
        System.out.println("*".repeat(80));
    }

    // _Accessors_

    public static String ArticlestoText(List<Article> Articles) {
        String text = "";
        for (Article article : Articles) {
            text = text + article.description;
        }
        return text;
    }

    public String getTitleArticle() {
        return title;
    }

    public String getDescriptionArticle() {
        return description;
    }

    public String getPubDateArticle() {
        return pubDate;
    }

    public String getLink() {
        return link;
    }
}