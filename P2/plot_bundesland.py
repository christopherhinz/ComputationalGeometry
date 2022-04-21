import xml.etree.ElementTree as ET

tree = ET.parse('DeutschlandMitStaedten.svg')
root = tree.getroot()


for p in root.findall('svg'):
    print(p.find(''))