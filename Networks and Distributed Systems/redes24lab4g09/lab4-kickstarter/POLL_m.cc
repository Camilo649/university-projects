//
// Generated file, do not edit! Created by opp_msgtool 6.0 from POLL.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "POLL_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

void __doPacking(omnetpp::cCommBuffer *b, const Info& a)
{
    doParsimPacking(b,a.id);
    doParsimPacking(b,a.hops);
    doParsimPacking(b,a.receptionTime);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Info& a)
{
    doParsimUnpacking(b,a.id);
    doParsimUnpacking(b,a.hops);
    doParsimUnpacking(b,a.receptionTime);
}

class InfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
        FIELD_hops,
        FIELD_receptionTime,
    };
  public:
    InfoDescriptor();
    virtual ~InfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(InfoDescriptor)

InfoDescriptor::InfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Info)), "")
{
    propertyNames = nullptr;
}

InfoDescriptor::~InfoDescriptor()
{
    delete[] propertyNames;
}

bool InfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Info *>(obj)!=nullptr;
}

const char **InfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *InfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int InfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int InfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
        FD_ISEDITABLE,    // FIELD_hops
        FD_ISEDITABLE,    // FIELD_receptionTime
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *InfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
        "hops",
        "receptionTime",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int InfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hops") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "receptionTime") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *InfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_id
        "unsigned int",    // FIELD_hops
        "double",    // FIELD_receptionTime
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **InfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *InfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int InfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void InfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Info'", field);
    }
}

const char *InfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        case FIELD_id: return ulong2string(pp->id);
        case FIELD_hops: return ulong2string(pp->hops);
        case FIELD_receptionTime: return double2string(pp->receptionTime);
        default: return "";
    }
}

void InfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->id = string2ulong(value); break;
        case FIELD_hops: pp->hops = string2ulong(value); break;
        case FIELD_receptionTime: pp->receptionTime = string2double(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Info'", field);
    }
}

omnetpp::cValue InfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        case FIELD_id: return (omnetpp::intval_t)(pp->id);
        case FIELD_hops: return (omnetpp::intval_t)(pp->hops);
        case FIELD_receptionTime: return pp->receptionTime;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Info' as cValue -- field index out of range?", field);
    }
}

void InfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->id = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_hops: pp->hops = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_receptionTime: pp->receptionTime = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Info'", field);
    }
}

const char *InfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr InfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void InfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Info *pp = omnetpp::fromAnyPtr<Info>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Info'", field);
    }
}

Register_Class(POLL)

POLL::POLL(const char *name) : ::omnetpp::cPacket(name)
{
}

POLL::POLL(const POLL& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

POLL::~POLL()
{
    delete [] this->information;
}

POLL& POLL::operator=(const POLL& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void POLL::copy(const POLL& other)
{
    this->source = other.source;
    this->hopCount = other.hopCount;
    delete [] this->information;
    this->information = (other.information_arraysize==0) ? nullptr : new Info[other.information_arraysize];
    information_arraysize = other.information_arraysize;
    for (size_t i = 0; i < information_arraysize; i++) {
        this->information[i] = other.information[i];
    }
    this->side = other.side;
}

void POLL::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->hopCount);
    b->pack(information_arraysize);
    doParsimArrayPacking(b,this->information,information_arraysize);
    doParsimPacking(b,this->side);
}

void POLL::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->hopCount);
    delete [] this->information;
    b->unpack(information_arraysize);
    if (information_arraysize == 0) {
        this->information = nullptr;
    } else {
        this->information = new Info[information_arraysize];
        doParsimArrayUnpacking(b,this->information,information_arraysize);
    }
    doParsimUnpacking(b,this->side);
}

unsigned int POLL::getSource() const
{
    return this->source;
}

void POLL::setSource(unsigned int source)
{
    this->source = source;
}

unsigned int POLL::getHopCount() const
{
    return this->hopCount;
}

void POLL::setHopCount(unsigned int hopCount)
{
    this->hopCount = hopCount;
}

size_t POLL::getInformationArraySize() const
{
    return information_arraysize;
}

const Info& POLL::getInformation(size_t k) const
{
    if (k >= information_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)information_arraysize, (unsigned long)k);
    return this->information[k];
}

void POLL::setInformationArraySize(size_t newSize)
{
    Info *information2 = (newSize==0) ? nullptr : new Info[newSize];
    size_t minSize = information_arraysize < newSize ? information_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        information2[i] = this->information[i];
    delete [] this->information;
    this->information = information2;
    information_arraysize = newSize;
}

void POLL::setInformation(size_t k, const Info& information)
{
    if (k >= information_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)information_arraysize, (unsigned long)k);
    this->information[k] = information;
}

void POLL::insertInformation(size_t k, const Info& information)
{
    if (k > information_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)information_arraysize, (unsigned long)k);
    size_t newSize = information_arraysize + 1;
    Info *information2 = new Info[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        information2[i] = this->information[i];
    information2[k] = information;
    for (i = k + 1; i < newSize; i++)
        information2[i] = this->information[i-1];
    delete [] this->information;
    this->information = information2;
    information_arraysize = newSize;
}

void POLL::appendInformation(const Info& information)
{
    insertInformation(information_arraysize, information);
}

void POLL::eraseInformation(size_t k)
{
    if (k >= information_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)information_arraysize, (unsigned long)k);
    size_t newSize = information_arraysize - 1;
    Info *information2 = (newSize == 0) ? nullptr : new Info[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        information2[i] = this->information[i];
    for (i = k; i < newSize; i++)
        information2[i] = this->information[i+1];
    delete [] this->information;
    this->information = information2;
    information_arraysize = newSize;
}

bool POLL::getSide() const
{
    return this->side;
}

void POLL::setSide(bool side)
{
    this->side = side;
}

class POLLDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_source,
        FIELD_hopCount,
        FIELD_information,
        FIELD_side,
    };
  public:
    POLLDescriptor();
    virtual ~POLLDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(POLLDescriptor)

POLLDescriptor::POLLDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(POLL)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

POLLDescriptor::~POLLDescriptor()
{
    delete[] propertyNames;
}

bool POLLDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<POLL *>(obj)!=nullptr;
}

const char **POLLDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *POLLDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int POLLDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int POLLDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_source
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_information
        FD_ISEDITABLE,    // FIELD_side
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *POLLDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "hopCount",
        "information",
        "side",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int POLLDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "source") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "information") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "side") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *POLLDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_source
        "unsigned int",    // FIELD_hopCount
        "Info",    // FIELD_information
        "bool",    // FIELD_side
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **POLLDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *POLLDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int POLLDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_information: return pp->getInformationArraySize();
        default: return 0;
    }
}

void POLLDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_information: pp->setInformationArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'POLL'", field);
    }
}

const char *POLLDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string POLLDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_source: return ulong2string(pp->getSource());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_information: return "";
        case FIELD_side: return bool2string(pp->getSide());
        default: return "";
    }
}

void POLLDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_source: pp->setSource(string2ulong(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); break;
        case FIELD_side: pp->setSide(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'POLL'", field);
    }
}

omnetpp::cValue POLLDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_source: return (omnetpp::intval_t)(pp->getSource());
        case FIELD_hopCount: return (omnetpp::intval_t)(pp->getHopCount());
        case FIELD_information: return omnetpp::toAnyPtr(&pp->getInformation(i)); break;
        case FIELD_side: return pp->getSide();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'POLL' as cValue -- field index out of range?", field);
    }
}

void POLLDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_source: pp->setSource(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_side: pp->setSide(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'POLL'", field);
    }
}

const char *POLLDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_information: return omnetpp::opp_typename(typeid(Info));
        default: return nullptr;
    };
}

omnetpp::any_ptr POLLDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        case FIELD_information: return omnetpp::toAnyPtr(&pp->getInformation(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void POLLDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    POLL *pp = omnetpp::fromAnyPtr<POLL>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'POLL'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

