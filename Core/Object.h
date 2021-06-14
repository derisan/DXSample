#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT,
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};


class Object
{
public:
	Object(OBJECT_TYPE type);
	virtual ~Object() = default;

	OBJECT_TYPE GetType() const { return mObjectType; }
	const std::wstring& GetName() const { return mName; }

protected:
	friend class ResourceManager;
	virtual void Load(const std::wstring& path) {}
	virtual void Save(const std::wstring& path) {}

private:
	OBJECT_TYPE mObjectType = OBJECT_TYPE::NONE;
	std::wstring mName = {};
};

