#pragma once
class Object abstract
{
protected:

	string _name;
	string _tag;

	Object* _parent = nullptr;
	list<Object*> _children;
	bool _allowsUpdate = true;

public:
	virtual HRESULT Init() { return S_OK; }
	virtual void Release() {}
	virtual void Update();
	virtual void Render() {}

	void SetParent(Object* parent);
	void AddChild(Object* child);
	void RemoveChild(Object* child);
	void SetAllowsUpdate(bool allowsUpdate) { _allowsUpdate = allowsUpdate; }
	bool GetAllowsUpdate() { return _allowsUpdate; }


	//Getter
	Object* GetParent() { return _parent; }
	list<Object*> GetChildren() { return _children; }
	string GetName() { return _name; }
	string GetTag() { return _tag; }
	Object* GetChildByName(string name)
	{
		for (Object* c : _children)
		{
			if (c->GetName() == name)
				return c;
		}
		return nullptr;
	}

	//Setter
	void SetName(string name) { _name = name; }
	void SetTag(string tag) { _tag = tag; }

};


