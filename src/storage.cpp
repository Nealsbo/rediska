#include "storage.h"



Storage::Storage() {

}

Storage::~Storage() {

}

void Storage::Init() {
    storage_imp = std::make_unique<ThreadSafeMap<std::string, std::string>>(53);
}

void Storage::Insert(const std::string& key, const std::string& value) {
    storage_imp->Insert(key, value);
}

void Storage::Delete(const std::string& key) {
    storage_imp->Delete(key);
}
    
std::string Storage::Find(const std::string& key) {
    return storage_imp->Find(key);
}

void Storage::Clear() {
    storage_imp->Clear();
}

bool Storage::IsEmpty() {
    return storage_imp->IsEmpty();
}
    
void Storage::Shutdown() {
    if(!storage_imp->IsEmpty()) {
        storage_imp->Clear();
    }
}