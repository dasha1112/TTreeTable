#include "TTreeNode.h"
#include "TTree.h"
#include "gtests.h"

TEST(TTreeNodeTest, DefaultConstructor) {
  TTreeNode<int, int> node;
  // Проверка, что все поля инициализированы правильно
  EXPECT_EQ(node.GetKey(), nullptr);
  EXPECT_EQ(node.GetVal(), nullptr);
}

// Тестирование конструктора с параметрами
TEST(TTreeNodeTest, ParameterizedConstructor)
{
  TTreeNode<int, int> node (new int(1), new int (10), nullptr, nullptr, nullptr);
  EXPECT_EQ(*(node.GetKey()), 1);
  EXPECT_EQ(*(node.GetVal()), 10);
}

// Тестирование конструктора копирования
TEST(TTreeNodeTest, CopyConstructor) {
  TTreeNode<int, int> originalNode(new int (3), new int (100), nullptr, nullptr, nullptr);
  TTreeNode<int, int> copiedNode(originalNode);
  EXPECT_EQ(*(copiedNode.GetKey()), 3);
  EXPECT_EQ(*(copiedNode.GetVal()), 100);
}

// Тестирование конструктора по умолчанию
TEST(TTreeTable, Constructor) 
{
  TTreeTable<int, int> tree;
  EXPECT_EQ(tree.GetCount(), 0);
  ASSERT_EQ(tree.GetRoot(), nullptr);
}

// Тестирование метода Add
TEST(TTreeTable, Add) {
  TTreeTable<int, int> treeTable;
  treeTable.Add(new int(3), new int (20));
  EXPECT_EQ(1, treeTable.GetCount());
  TTreeNode<int, int>* root = treeTable.GetRoot();
  EXPECT_NE(nullptr, root);
  EXPECT_EQ(3, *(root->GetKey()));
}

// Тестирование метода Find
TEST(TTreeTable, Find) {
  TTreeTable<int, std::string> treeTable;
  std::string value = "test value";
  treeTable.Add(new int(10), &value);
  TTreeNode<int, std::string> node = treeTable.Find(10);
  EXPECT_EQ(*(node.GetKey()), 10);
  EXPECT_EQ(*(node.GetVal()), "test value");
}

// Тестирование метода Add с несколькими значениями
TEST(TTreeTable, AddMultipleSpecific) {
  TTreeTable<int, int> treeTable;
  treeTable.Add(new int(5), new int(50));
  treeTable.Add(new int(3), new int(30));
  treeTable.Add(new int(7), new int(70));
  treeTable.Add(new int(4), new int(40));
  treeTable.Add(new int(6), new int(60));
  treeTable.Add(new int(8), new int(80));
  treeTable.Add(new int(10), new int(100));
  treeTable.Add(new int(9), new int(90));

  EXPECT_EQ(8, treeTable.GetCount());

  TTreeNode<int, int>* root = treeTable.GetRoot();
  EXPECT_NE(nullptr, root);
  EXPECT_EQ(5, *(root->GetKey()));
  EXPECT_EQ(50, *(root->GetVal()));

  TTreeNode<int, int>* node3 = root->GetLeft();
  EXPECT_EQ(3, *(node3->GetKey()));
  EXPECT_EQ(30, *(node3->GetVal()));

  TTreeNode<int, int>* node7 = root->GetRight();
  EXPECT_EQ(7, *(node7->GetKey()));
  EXPECT_EQ(70, *(node7->GetVal()));

}

// Тестирование метода Find с несколькими значениями
TEST(TTreeTable, FindMultipleSpecific) {
  TTreeTable<int, std::string> treeTable;
  std::string value5 = "value for 5";
  std::string value3 = "value for 3";
  std::string value7 = "value for 7";
  treeTable.Add(new int(5), &value5);
  treeTable.Add(new int(3), &value3);
  treeTable.Add(new int(7), &value7);

  TTreeNode<int, std::string> node5 = treeTable.Find(5);
  EXPECT_EQ(*(node5.GetKey()), 5);
  EXPECT_EQ(*(node5.GetVal()), "value for 5");

  TTreeNode<int, std::string> node3 = treeTable.Find(3);
  EXPECT_EQ(*(node3.GetKey()), 3);
  EXPECT_EQ(*(node3.GetVal()), "value for 3");

  TTreeNode<int, std::string> node7 = treeTable.Find(7);
  EXPECT_EQ(*(node7.GetKey()), 7);
  EXPECT_EQ(*(node7.GetVal()), "value for 7");
}

// Тестирование оператора []
TEST(TTreeTable, OperatorBracket) {
  TTreeTable<int, int> tree;
  tree.Add(new int(3), new int(20));
  tree.Add(new int(6), new int(30));
  tree.Add(new int(4), new int(56));

  EXPECT_EQ(3, tree.GetCount());

  int k1 = 3;
  int k2 = 6;
  int k3 = 4;

  TTreeNode<int, int>* node1 = &tree[&k1];
  TTreeNode<int, int>* node2 = &tree[&k2];
  TTreeNode<int, int>* node3 = &tree[&k3];

  EXPECT_EQ(20, *(node1->GetVal()));
  EXPECT_EQ(30, *(node2->GetVal()));
  EXPECT_EQ(56, *(node3->GetVal()));
}
// Тестирование метода Clear
TEST(TTreeTable, ClearWithSingleElement) {
  TTreeTable<int, std::string> treeTable;
  std::string value5 = "value for 5";
  treeTable.Add(new int(5), &value5);

  EXPECT_EQ(1, treeTable.GetCount());

  treeTable.Clear();

  EXPECT_EQ(0, treeTable.GetCount());
  EXPECT_EQ(nullptr, treeTable.GetRoot());
}
// Тестирование метода Clear с несколькими элементами
TEST(TTreeTable, Clear) {
  TTreeTable<int, std::string> treeTable;
  std::string value5 = "value for 5";
  std::string value3 = "value for 3";
  treeTable.Add(new int(5), &value5);
  treeTable.Add(new int(3), &value3);

  EXPECT_EQ(2, treeTable.GetCount());

  treeTable.Clear();

  EXPECT_EQ(0, treeTable.GetCount());
  EXPECT_EQ(nullptr, treeTable.GetRoot());
}





