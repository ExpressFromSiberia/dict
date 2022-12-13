#pragma once

#include <map>

template<class Key, class Value>
class dictionary {
public:

    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception {
public:
    virtual const Key& get_key() const noexcept = 0;
};

template<class Key>
class m_exception : public not_found_exception<Key> {
private:
    const Key err_key;
    const std::string err_msg;

public:
    m_exception(const Key& value, const std::string& msg) : err_key(value), err_msg(msg)
    {}

    const Key& get_key() const noexcept override {
        return err_key;
    }

    const char* what() const noexcept override {
        return err_msg.c_str();
    }
};

template<class Key, class Value>
class m_dict : public dictionary<Key, Value> {
private:
    typedef std::map<Key, Value> _dict_map;
    _dict_map dict;

public:
    m_dict() : dict()
    {}
    ~m_dict() = default;

    const Value& get(const Key& key) const override {
        typename _dict_map::const_iterator it = dict.find(key);
        if (it != dict.end())
            return it->second;
        else
            throw m_exception<Key>(key, "Value with this key not found!");
    }

    void set(const Key& key, const Value& value) override {
        dict.insert({ key, value });
    }

    bool is_set(const Key& key) const override {
        return dict.find(key) != dict.end();
    }
};