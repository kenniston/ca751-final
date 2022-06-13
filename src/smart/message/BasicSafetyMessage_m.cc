//
// Generated file, do not edit! Created by opp_msgtool 6.0 from smart/message/BasicSafetyMessage.msg.
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
#include "BasicSafetyMessage_m.h"

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

namespace veins {

Register_Class(BasicSafetyMessage)

BasicSafetyMessage::BasicSafetyMessage(const char *name) : ::veins::BaseFrame1609_4(name)
{
}

BasicSafetyMessage::BasicSafetyMessage(const BasicSafetyMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

BasicSafetyMessage::~BasicSafetyMessage()
{
}

BasicSafetyMessage& BasicSafetyMessage::operator=(const BasicSafetyMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void BasicSafetyMessage::copy(const BasicSafetyMessage& other)
{
    this->senderId = other.senderId;
    this->senderPos = other.senderPos;
    this->senderSpeed = other.senderSpeed;
    this->senderHeading = other.senderHeading;
    this->senderGpsPos = other.senderGpsPos;
    this->senderAccel = other.senderAccel;
    this->senderWidth = other.senderWidth;
    this->senderLength = other.senderLength;
    this->senderType = other.senderType;
    this->senderAttackType = other.senderAttackType;
    this->senderPseudonym = other.senderPseudonym;
    this->rsu = other.rsu;
}

void BasicSafetyMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->senderHeading);
    doParsimPacking(b,this->senderGpsPos);
    doParsimPacking(b,this->senderAccel);
    doParsimPacking(b,this->senderWidth);
    doParsimPacking(b,this->senderLength);
    doParsimPacking(b,this->senderType);
    doParsimPacking(b,this->senderAttackType);
    doParsimPacking(b,this->senderPseudonym);
    doParsimPacking(b,this->rsu);
}

void BasicSafetyMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->senderSpeed);
    doParsimUnpacking(b,this->senderHeading);
    doParsimUnpacking(b,this->senderGpsPos);
    doParsimUnpacking(b,this->senderAccel);
    doParsimUnpacking(b,this->senderWidth);
    doParsimUnpacking(b,this->senderLength);
    doParsimUnpacking(b,this->senderType);
    doParsimUnpacking(b,this->senderAttackType);
    doParsimUnpacking(b,this->senderPseudonym);
    doParsimUnpacking(b,this->rsu);
}

const LAddress::L2Type& BasicSafetyMessage::getSenderId() const
{
    return this->senderId;
}

void BasicSafetyMessage::setSenderId(const LAddress::L2Type& senderId)
{
    this->senderId = senderId;
}

const Coord& BasicSafetyMessage::getSenderPos() const
{
    return this->senderPos;
}

void BasicSafetyMessage::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

const Coord& BasicSafetyMessage::getSenderSpeed() const
{
    return this->senderSpeed;
}

void BasicSafetyMessage::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

const Coord& BasicSafetyMessage::getSenderHeading() const
{
    return this->senderHeading;
}

void BasicSafetyMessage::setSenderHeading(const Coord& senderHeading)
{
    this->senderHeading = senderHeading;
}

const Coord& BasicSafetyMessage::getSenderGpsPos() const
{
    return this->senderGpsPos;
}

void BasicSafetyMessage::setSenderGpsPos(const Coord& senderGpsPos)
{
    this->senderGpsPos = senderGpsPos;
}

double BasicSafetyMessage::getSenderAccel() const
{
    return this->senderAccel;
}

void BasicSafetyMessage::setSenderAccel(double senderAccel)
{
    this->senderAccel = senderAccel;
}

double BasicSafetyMessage::getSenderWidth() const
{
    return this->senderWidth;
}

void BasicSafetyMessage::setSenderWidth(double senderWidth)
{
    this->senderWidth = senderWidth;
}

double BasicSafetyMessage::getSenderLength() const
{
    return this->senderLength;
}

void BasicSafetyMessage::setSenderLength(double senderLength)
{
    this->senderLength = senderLength;
}

int BasicSafetyMessage::getSenderType() const
{
    return this->senderType;
}

void BasicSafetyMessage::setSenderType(int senderType)
{
    this->senderType = senderType;
}

int BasicSafetyMessage::getSenderAttackType() const
{
    return this->senderAttackType;
}

void BasicSafetyMessage::setSenderAttackType(int senderAttackType)
{
    this->senderAttackType = senderAttackType;
}

unsigned long BasicSafetyMessage::getSenderPseudonym() const
{
    return this->senderPseudonym;
}

void BasicSafetyMessage::setSenderPseudonym(unsigned long senderPseudonym)
{
    this->senderPseudonym = senderPseudonym;
}

bool BasicSafetyMessage::getRsu() const
{
    return this->rsu;
}

void BasicSafetyMessage::setRsu(bool rsu)
{
    this->rsu = rsu;
}

class BasicSafetyMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderId,
        FIELD_senderPos,
        FIELD_senderSpeed,
        FIELD_senderHeading,
        FIELD_senderGpsPos,
        FIELD_senderAccel,
        FIELD_senderWidth,
        FIELD_senderLength,
        FIELD_senderType,
        FIELD_senderAttackType,
        FIELD_senderPseudonym,
        FIELD_rsu,
    };
  public:
    BasicSafetyMessageDescriptor();
    virtual ~BasicSafetyMessageDescriptor();

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

Register_ClassDescriptor(BasicSafetyMessageDescriptor)

BasicSafetyMessageDescriptor::BasicSafetyMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::BasicSafetyMessage)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

BasicSafetyMessageDescriptor::~BasicSafetyMessageDescriptor()
{
    delete[] propertyNames;
}

bool BasicSafetyMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BasicSafetyMessage *>(obj)!=nullptr;
}

const char **BasicSafetyMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BasicSafetyMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BasicSafetyMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int BasicSafetyMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_senderId
        0,    // FIELD_senderPos
        0,    // FIELD_senderSpeed
        0,    // FIELD_senderHeading
        0,    // FIELD_senderGpsPos
        FD_ISEDITABLE,    // FIELD_senderAccel
        FD_ISEDITABLE,    // FIELD_senderWidth
        FD_ISEDITABLE,    // FIELD_senderLength
        FD_ISEDITABLE,    // FIELD_senderType
        FD_ISEDITABLE,    // FIELD_senderAttackType
        FD_ISEDITABLE,    // FIELD_senderPseudonym
        FD_ISEDITABLE,    // FIELD_rsu
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *BasicSafetyMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderId",
        "senderPos",
        "senderSpeed",
        "senderHeading",
        "senderGpsPos",
        "senderAccel",
        "senderWidth",
        "senderLength",
        "senderType",
        "senderAttackType",
        "senderPseudonym",
        "rsu",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int BasicSafetyMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "senderPos") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "senderSpeed") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "senderHeading") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "senderGpsPos") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "senderAccel") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "senderWidth") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "senderLength") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "senderType") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "senderAttackType") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "senderPseudonym") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "rsu") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *BasicSafetyMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "veins::LAddress::L2Type",    // FIELD_senderId
        "veins::Coord",    // FIELD_senderPos
        "veins::Coord",    // FIELD_senderSpeed
        "veins::Coord",    // FIELD_senderHeading
        "veins::Coord",    // FIELD_senderGpsPos
        "double",    // FIELD_senderAccel
        "double",    // FIELD_senderWidth
        "double",    // FIELD_senderLength
        "int",    // FIELD_senderType
        "int",    // FIELD_senderAttackType
        "unsigned long",    // FIELD_senderPseudonym
        "bool",    // FIELD_rsu
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **BasicSafetyMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *BasicSafetyMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BasicSafetyMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BasicSafetyMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BasicSafetyMessage'", field);
    }
}

const char *BasicSafetyMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BasicSafetyMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return "";
        case FIELD_senderPos: return "";
        case FIELD_senderSpeed: return "";
        case FIELD_senderHeading: return "";
        case FIELD_senderGpsPos: return "";
        case FIELD_senderAccel: return double2string(pp->getSenderAccel());
        case FIELD_senderWidth: return double2string(pp->getSenderWidth());
        case FIELD_senderLength: return double2string(pp->getSenderLength());
        case FIELD_senderType: return long2string(pp->getSenderType());
        case FIELD_senderAttackType: return long2string(pp->getSenderAttackType());
        case FIELD_senderPseudonym: return ulong2string(pp->getSenderPseudonym());
        case FIELD_rsu: return bool2string(pp->getRsu());
        default: return "";
    }
}

void BasicSafetyMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderAccel: pp->setSenderAccel(string2double(value)); break;
        case FIELD_senderWidth: pp->setSenderWidth(string2double(value)); break;
        case FIELD_senderLength: pp->setSenderLength(string2double(value)); break;
        case FIELD_senderType: pp->setSenderType(string2long(value)); break;
        case FIELD_senderAttackType: pp->setSenderAttackType(string2long(value)); break;
        case FIELD_senderPseudonym: pp->setSenderPseudonym(string2ulong(value)); break;
        case FIELD_rsu: pp->setRsu(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicSafetyMessage'", field);
    }
}

omnetpp::cValue BasicSafetyMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return omnetpp::toAnyPtr(&pp->getSenderId()); break;
        case FIELD_senderPos: return omnetpp::toAnyPtr(&pp->getSenderPos()); break;
        case FIELD_senderSpeed: return omnetpp::toAnyPtr(&pp->getSenderSpeed()); break;
        case FIELD_senderHeading: return omnetpp::toAnyPtr(&pp->getSenderHeading()); break;
        case FIELD_senderGpsPos: return omnetpp::toAnyPtr(&pp->getSenderGpsPos()); break;
        case FIELD_senderAccel: return pp->getSenderAccel();
        case FIELD_senderWidth: return pp->getSenderWidth();
        case FIELD_senderLength: return pp->getSenderLength();
        case FIELD_senderType: return pp->getSenderType();
        case FIELD_senderAttackType: return pp->getSenderAttackType();
        case FIELD_senderPseudonym: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getSenderPseudonym());
        case FIELD_rsu: return pp->getRsu();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BasicSafetyMessage' as cValue -- field index out of range?", field);
    }
}

void BasicSafetyMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderAccel: pp->setSenderAccel(value.doubleValue()); break;
        case FIELD_senderWidth: pp->setSenderWidth(value.doubleValue()); break;
        case FIELD_senderLength: pp->setSenderLength(value.doubleValue()); break;
        case FIELD_senderType: pp->setSenderType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_senderAttackType: pp->setSenderAttackType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_senderPseudonym: pp->setSenderPseudonym(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        case FIELD_rsu: pp->setRsu(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicSafetyMessage'", field);
    }
}

const char *BasicSafetyMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BasicSafetyMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return omnetpp::toAnyPtr(&pp->getSenderId()); break;
        case FIELD_senderPos: return omnetpp::toAnyPtr(&pp->getSenderPos()); break;
        case FIELD_senderSpeed: return omnetpp::toAnyPtr(&pp->getSenderSpeed()); break;
        case FIELD_senderHeading: return omnetpp::toAnyPtr(&pp->getSenderHeading()); break;
        case FIELD_senderGpsPos: return omnetpp::toAnyPtr(&pp->getSenderGpsPos()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BasicSafetyMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicSafetyMessage *pp = omnetpp::fromAnyPtr<BasicSafetyMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicSafetyMessage'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

