package feed;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

public class FeedParser {

    public static List<Article> parseXML(String xmlData) {
        List<Article> articulos = new ArrayList<Article>();
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document doc = builder.parse(new InputSource(new StringReader(xmlData)));
            NodeList items = doc.getElementsByTagName("item");
            // creamos una lista de nodos con todo aquello que encierran las etiquetas
            // <item> <\item>
            for (int i = 0; i < items.getLength(); i++) {
                Node node = items.item(i);
                Element itemElement = (Element) node;
                // por cada nodo de item creamos una lista para parsear los titulos,
                // descripcion, pubDate y link.
                NodeList titles = itemElement.getElementsByTagName("title");
                String title = titles.item(0) != null ? titles.item(0).getTextContent() : "";

                NodeList descriptions = itemElement.getElementsByTagName("description");
                String description = descriptions.item(0) != null ? descriptions.item(0).getTextContent() : "";

                NodeList pubDates = itemElement.getElementsByTagName("pubDate");
                String pubDate = pubDates.item(0) != null ? pubDates.item(0).getTextContent() : "";

                NodeList links = itemElement.getElementsByTagName("link");
                String link = links.item(0) != null ? links.item(0).getTextContent() : "";

                Article article = new Article(title, description, pubDate, link);
                articulos.add(article);
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return articulos;
    }

    public static String fetchFeed(String feedURL) throws MalformedURLException, IOException, Exception {

        URL url = new URL(feedURL);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();

        connection.setRequestMethod("GET");
        connection.setRequestProperty("Content-Type", "application/json");

        // Si todos los grupos usan el mismo user-agent, el servidor puede bloquear las
        // solicitudes.
        connection.setRequestProperty("user-agent", "lab_paradigmas"); // con g36 no rechaza la solicitud p12pais y
                                                                       // p12eco
        connection.setConnectTimeout(5000);
        connection.setReadTimeout(5000);

        int status = connection.getResponseCode();
        if (status != 200) {
            throw new Exception("HTTP error code: " + status);
        } else {
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            StringBuffer content = new StringBuffer();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            in.close();
            connection.disconnect();
            return content.toString();
        }
    }
}
