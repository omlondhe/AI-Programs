class FamilyMember:
    def __init__(self, name) -> None:
        self.name = name
        self.parents: list[FamilyMember] = []
        self.mother: FamilyMember = None
        self.father: FamilyMember = None
        self.children: list[FamilyMember] = []
        self.siblings: list[FamilyMember] = []
        self.wife: FamilyMember = None
        self.husband: FamilyMember = None
        self.pets: list[FamilyMember] = []
    
    def setName(self, name: str) -> None:
        self.name = name
    
    def addParent(self, parent) -> None:
        if not self.parents.__contains__(parent):
            self.parents.append(parent)
    
    def setMother(self, mother) -> None:
        self.mother = mother
        self.addParent(mother)
    
    def setFather(self, father) -> None:
        self.father = father
        self.addParent(father)
    
    def addChild(self, child) -> None:
        if not self.children.__contains__(child):
            self.children.append(child)
    
    def setSiblings(self, siblings: list) -> None:
        self.siblings = siblings
    
    def addSibling(self, sibling) -> None:
        if not self.siblings.__contains__(sibling):
            self.siblings.append(sibling)

    def setWife(self, wife) -> None:
        self.wife = wife
    
    def setHusband(self, husband) -> None:
        self.husband = husband
    
    def setPets(self, pets: list) -> None:
        self.pets = pets

    def addPet(self, pet) -> None:
        if not self.pets.__contains__(pet):
            self.pets.append(pet)


def createMyFamily(om: FamilyMember):
    grandMotherM: FamilyMember = FamilyMember("Lata Jivrakh")
    grandFatherM: FamilyMember = FamilyMember("Sudhakar Jivrakh")

    mother: FamilyMember = FamilyMember("Urmila Londhe")
    motherSibling1: FamilyMember = FamilyMember("Sharmila Shirke")
    motherSibling2: FamilyMember = FamilyMember("Bhagyashree Shinde")
    motherSibling3: FamilyMember = FamilyMember("Shital Thakar")
    motherSibling4: FamilyMember = FamilyMember("Rushikesh Jivrakh")
    motherSibling4Wife: FamilyMember = FamilyMember("Snehal Jivrakh")

    grandMotherM.setHusband(grandFatherM)
    grandFatherM.setWife(grandMotherM)

    grandMotherM.addChild(mother)
    grandFatherM.addChild(mother)
    grandMotherM.addChild(motherSibling1)
    grandFatherM.addChild(motherSibling1)
    grandMotherM.addChild(motherSibling2)
    grandFatherM.addChild(motherSibling2)
    grandMotherM.addChild(motherSibling3)
    grandFatherM.addChild(motherSibling3)
    grandMotherM.addChild(motherSibling4)
    grandFatherM.addChild(motherSibling4)

    motherSibling4Wife.setHusband(motherSibling4)

    for child in grandMotherM.children:
        child.setMother(grandMotherM)
        child.setFather(grandFatherM)
        if child != mother:
            mother.addSibling(child)
        if child != motherSibling1:
            motherSibling1.addChild(child)
        if child != motherSibling1:
            motherSibling1.addChild(child)
        if child != motherSibling3:
            motherSibling3.addChild(child)
        if child != motherSibling4:
            motherSibling4.addChild(child)
    
    grandMotherF: FamilyMember = FamilyMember("Saraswati Londhe")
    grandFatherF: FamilyMember = FamilyMember("Achutrao Londhe")

    grandMotherF.setHusband(grandFatherF)
    grandFatherF.setWife(grandMotherF)

    father: FamilyMember = FamilyMember("Prashant Londhe")

    father.setWife(mother)
    mother.setHusband(father)
    father.setFather(grandFatherF)
    father.setMother(grandMotherF)

    bhargavi: FamilyMember = FamilyMember("Bhargavi Londhe")
    luffy: FamilyMember = FamilyMember("Luffy")

    bhargavi.setFather(father)
    bhargavi.setMother(mother)
    om.setFather(father)
    om.setMother(mother)

    luffy.setFather(father)
    luffy.setMother(mother)
    luffy.addParent(om)
    luffy.addParent(bhargavi)

    father.addChild(om)
    mother.addChild(om)
    father.addChild(bhargavi)
    mother.addChild(bhargavi)

    father.addPet(luffy)
    mother.addPet(luffy)
    om.addPet(luffy)
    mother.addPet(luffy)

    om.addSibling(bhargavi)
    bhargavi.addSibling(om)


om: FamilyMember = FamilyMember("Om Londhe")
createMyFamily(om)

print(f"Me: {om.name}")
print(f"Mother: {om.mother.name}")
print(f"Father: {om.father.name}")
print(f"Siblings: {[sibling.name for sibling in om.siblings]}")
print(f"Grand Mother M: {om.mother.mother.name}")
print(f"Grand Father M: {om.mother.father.name}")
print(f"Grand Mother F: {om.father.mother.name}")
print(f"Grand Father F: {om.father.father.name}")
print(f"Mother siblings: {[sibling.name for sibling in om.mother.siblings]}")
print(f"Pet: {[pet.name for pet in om.pets]}")
