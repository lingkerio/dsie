package main

type AVLNode struct {
	Data   int
	Height int
	Left   *AVLNode
	Right  *AVLNode
}

func Height(node *AVLNode) int {
	if node == nil {
		return -1
	}
	return node.Height
}

func updateHeight(node *AVLNode) int{
	node.Height = 1 + max(Height(node.Left), Height(node.Right))
	return node.Height
}

func balanceFactor(node *AVLNode) int {
	if node == nil {
		return 0
	}
	return Height(node.Left) - Height(node.Right)
}

func CreateNode(value int) *AVLNode {
	return &AVLNode{
		Data:   value,
		Height: 0,
		Left:   nil,
		Right:  nil,
	}
}

func RightRotate(node *AVLNode) *AVLNode {
	child := node.Left
	grandChild := child.Right
	child.Right = node
	node.Left = grandChild
	node.Height = updateHeight(node)
	child.Height = updateHeight(child)
	return child
}

func LeftRotate(node *AVLNode) *AVLNode {
	child := node.Right
	grandChild := child.Left
	child.Left = node
	node.Right = grandChild
	node.Height = updateHeight(node)
	child.Height = updateHeight(child)
	return child
}

func ReBalance(node *AVLNode) *AVLNode {
	if node == nil {
		return nil
	}

	node.Height = updateHeight(node)

	balance := balanceFactor(node)

	if balance > 1 {
		if balanceFactor(node.Left) < 0 {
			node.Left = LeftRotate(node.Left)
		}
		node = RightRotate(node)
	} else if balance < -1 {
		if balanceFactor(node.Right) > 0 {
			node.Right = RightRotate(node.Right)
		}
		node = LeftRotate(node)
	}

	return node
}

func FindMin(node *AVLNode) *AVLNode {
	if node == nil {
		return nil
	}

	current := node
	for current.Left != nil {
		current = current.Left
	}

	return current
}

func FindMax(node *AVLNode) *AVLNode {
	if node == nil {
		return nil
	}

	current := node
	for current.Right != nil {
		current = current.Right
	}

	return current
}

func Insert(node *AVLNode, data int) *AVLNode {
	if node == nil {
		return CreateNode(data)
	}

	if data < node.Data {
		node.Left = Insert(node.Left, data)
	} else if data > node.Data {
		node.Right = Insert(node.Right, data)
	}

	node.Height = updateHeight(node)
	return ReBalance(node)
}

func Search(node *AVLNode, data int) bool {
	if node == nil {
		return false
	}

	if data < node.Data {
		return Search(node.Left, data)
	} else if data > node.Data {
		return Search(node.Right, data)
	}

	return true
}

func Remove(node *AVLNode, data int) *AVLNode {
	if node == nil {
		return nil
	}

	if data < node.Data {
		node.Left = Remove(node.Left, data)
	} else if data > node.Data {
		node.Right = Remove(node.Right, data)
	} else {
		if node.Left == nil && node.Right == nil {
			node = nil
		} else if node.Left == nil {
			node = node.Right
		} else if node.Right == nil {
			node = node.Left
		} else {
			temp := FindMin(node.Right)
			node.Data = temp.Data
			node.Right = Remove(node.Right, temp.Data)
		}
	}
	if node == nil {
		return node
	}

	node.Height = updateHeight(node)

	return ReBalance(node)
}
