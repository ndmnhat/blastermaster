using System;
using System.IO;
using System.IO.Enumeration;
using System.Xml.Linq;
using System.Linq;
using System.Security.Principal;

namespace tmxtotxt
{
    class Program
    {
        static void Main(string[] args)
        {
            string fileName = args[0];
            string txtFile = args[2];

            // Create file stream
            if (File.Exists(txtFile))
                File.Delete(txtFile);
            StreamWriter sw = File.CreateText(txtFile);

            // Load tmx file
            var xDoc = XDocument.Load(fileName);

            // Parse map info
            var mapWidth = Convert.ToInt32(xDoc.Root.Attribute("width").Value);
            var mapHeight = Convert.ToInt32(xDoc.Root.Attribute("height").Value);
            var tileWidth = Convert.ToInt32(xDoc.Root.Attribute("tilewidth").Value);
            var tileHeight = Convert.ToInt32(xDoc.Root.Attribute("tileheight").Value);
            var tilecount = Convert.ToInt32(xDoc.Root.Element("tileset").Attribute("tilecount").Value);
            sw.WriteLine("{0} {1} {2} {3} {4}", mapWidth, mapHeight, tileWidth, tileHeight, tilecount);

            // Parse tile data
            var layer = (from c in xDoc.Root.Elements("layer")
                        where c.Attribute("id").Value == args[1]
                        select c).FirstOrDefault();
            var tiles = layer.Element("data").Elements().ToList();
            for(int i = 0; i < mapHeight*mapWidth; ++i)
            {
                if (i % mapWidth == mapWidth-1)
                    sw.Write(tiles[i].Attribute("gid").Value + "\n");
                else
                    sw.Write(tiles[i].Attribute("gid").Value + " ");
            }
            sw.Close();
        }
    }
}
