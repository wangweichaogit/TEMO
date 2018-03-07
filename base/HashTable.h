/*
author£ºwwc
wirte by:2018/03/06
*/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_


#include <list>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

template<typename Key,typename Value,typename Hash=std::hash<Key> >
class HashTable
{
private:
	class bucket_type
	{
	private:
		using bucket_value = std::pair<Key, Value>;
		using bucket_data = std::list<bucket_value>;
//		using bucket_iterator = typename bucket_data::iterator;
		typedef typename bucket_data::iterator bucket_iterator;
		bucket_data data;
		bucket_iterator get_entry_for(const Key & key) 
		{	
			return std::find_if(std::begin(data), std::end(data),[&](const bucket_value &item){return item.first == key;});
		}
	public:
		void add_or_update_mapping(const Key&key, const Value &value)
		{
			bucket_iterator  it = get_entry_for(key);
			if (it == data.end())
				data.push_back(bucket_value(key, value));
			else
				it->second = value;
		}

		void remove_mapping(const Key &key)
		{
			bucket_iterator  it = get_entry_for(key);
			if (it != data.end())
				data.erase(it);
		}

		Value value_for(const Key& key, const Value & default_value /* = Value() */)
		{
			bucket_iterator it = get_entry_for(key);
			return (it == data.end()) ? default_value:it->second;
		}
	};
	std::vector<std::unique_ptr<bucket_type>> buckets;
	Hash     hasher;
	bucket_type & get_bucket(const Key & key)
	{
		std::size_t index = hasher(key) % buckets.size();
		return *buckets[index];
	}
public:
	HashTable(unsigned size_ = 19, const Hash & hasher_ = Hash()) :buckets(size_),hasher(hasher_)
	{
		for (int index=0;index<size_;index++)
		{
			buckets[index].reset(new bucket_type);
		}
	}

	HashTable(const HashTable &other) = delete;
	const HashTable& operator=(const HashTable& other) = delete;

	void add_or_update_mapping(const Key&key, const Value &value)
	{
		get_bucket(key).add_or_update_mapping(key, value);
	}

	void remove_mapping(const Key &key)
	{
		get_bucket(key).remove_mapping(key);
	}

	Value value_for(const Key& key, const Value & default_value  = Value() )
	{
		return get_bucket(key).value_for(key, default_value);
	}
};



#endif



