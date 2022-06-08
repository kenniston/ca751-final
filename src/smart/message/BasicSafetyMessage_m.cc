//
// Generated file, do not edit! Created by opp_msgtool 6.0 from smart/messages/BasicSafetyMessage.msg.
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
#include "../message/BasicSafetyMessage_m.h"

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
    this->senderPos = other.senderPos;
    this->senderPosConfidence = other.senderPosConfidence;
    this->senderSpeed = other.senderSpeed;
    this->senderSpeedConfidence = other.senderSpeedConfidence;
    this->senderHeading = other.senderHeading;
    this->senderHeadingConfidence = other.senderHeadingConfidence;
    this->senderAccel = other.senderAccel;
    this->senderAccelConfidence = other.senderAccelConfidence;
    this->senderWidth = other.senderWidth;
    this->senderLength = other.senderLength;
    this->senderMbType = other.senderMbType;
    this->senderAttackType = other.senderAttackType;
    this->senderGpsCoordinates = other.senderGpsCoordinates;
    this->senderRealId = other.senderRealId;
    this->senderPseudonym = other.senderPseudonym;
}

void BasicSafetyMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderPosConfidence);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->senderSpeedConfidence);
    doParsimPacking(b,this->senderHeading);
    doParsimPacking(b,this->senderHeadingConfidence);
    doParsimPacking(b,this->senderAccel);
    doParsimPacking(b,this->senderAccelConfidence);
    doParsimPacking(b,this->senderWidth);
    doParsimPacking(b,this->senderLength);
    doParsimPacking(b,this->senderMbType);
    doParsimPacking(b,this->senderAttackType);
    doParsimPacking(b,this->senderGpsCoordinates);
    doParsimPacking(b,this->senderRealId);
    doParsimPacking(b,this->senderPseudonym);
}

void BasicSafetyMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->senderPosConfidence);
    doParsimUnpacking(b,this->senderSpeed);
    doParsimUnpacking(b,this->senderSpeedConfidence);
    doParsimUnpacking(b,this->senderHeading);
    doParsimUnpacking(b,this->senderHeadingConfidence);
    doParsimUnpacking(b,this->senderAccel);
    doParsimUnpacking(b,this->senderAccelConfidence);
    doParsimUnpacking(b,this->senderWidth);
    doParsimUnpacking(b,this->senderLength);
    doParsimUnpacking(b,this->senderMbType);
    doParsimUnpacking(b,this->senderAttackType);
    doParsimUnpacking(b,this->senderGpsCoordinates);
    doParsimUnpacking(b,this->senderRealId);
    doParsimUnpacking(b,this->senderPseudonym);
}

const Coord& BasicSafetyMessage::getSenderPos() const
{
    return this->senderPos;
}

void BasicSafetyMessage::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

const Coord& BasicSafetyMessage::getSenderPosConfidence() const
{
    return this->senderPosConfidence;
}

void BasicSafetyMessage::setSenderPosConfidence(const Coord& senderPosConfidence)
{
    this->senderPosConfidence = senderPosConfidence;
}

const Coord& BasicSafetyMessage::getSenderSpeed() const
{
    return this->senderSpeed;
}

void BasicSafetyMessage::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

const Coord& BasicSafetyMessage::getSenderSpeedConfidence() const
{
    return this->senderSpeedConfidence;
}

void BasicSafetyMessage::setSenderSpeedConfidence(const Coord& senderSpeedConfidence)
{
    this->senderSpeedConfidence = senderSpeedConfidence;
}

const Coord& BasicSafetyMessage::getSenderHeading() const
{
    return this->senderHeading;
}

void BasicSafetyMessage::setSenderHeading(const Coord& senderHeading)
{
    this->senderHeading = senderHeading;
}

const Coord& BasicSafetyMessage::getSenderHeadingConfidence() const
{
    return this->senderHeadingConfidence;
}

void BasicSafetyMessage::setSenderHeadingConfidence(const Coord& senderHeadingConfidence)
{
    this->senderHeadingConfidence = senderHeadingConfidence;
}

const Coord& BasicSafetyMessage::getSenderAccel() const
{
    return this->senderAccel;
}

void BasicSafetyMessage::setSenderAccel(const Coord& senderAccel)
{
    this->senderAccel = senderAccel;
}

const Coord& BasicSafetyMessage::getSenderAccelConfidence() const
{
    return this->senderAccelConfidence;
}

void BasicSafetyMessage::setSenderAccelConfidence(const Coord& senderAccelConfidence)
{
    this->senderAccelConfidence = senderAccelConfidence;
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

int BasicSafetyMessage::getSenderMbType() const
{
    return this->senderMbType;
}

void BasicSafetyMessage::setSenderMbType(int senderMbType)
{
    this->senderMbType = senderMbType;
}

int BasicSafetyMessage::getSenderAttackType() const
{
    return this->senderAttackType;
}

void BasicSafetyMessage::setSenderAttackType(int senderAttackType)
{
    this->senderAttackType = senderAttackType;
}

const Coord& BasicSafetyMessage::getSenderGpsCoordinates() const
{
    return this->senderGpsCoordinates;
}

void BasicSafetyMessage::setSenderGpsCoordinates(const Coord& senderGpsCoordinates)
{
    this->senderGpsCoordinates = senderGpsCoordinates;
}

const LAddress::L2Type& BasicSafetyMessage::getSenderRealId() const
{
    return this->senderRealId;
}

void BasicSafetyMessage::setSenderRealId(const LAddress::L2Type& senderRealId)
{
    this->senderRealId = senderRealId;
}

unsigned long BasicSafetyMessage::getSenderPseudonym() const
{
    return this->senderPseudonym;
}

void BasicSafetyMessage::setSenderPseudonym(unsigned long senderPseudonym)
{
    this->senderPseudonym = senderPseudonym;
}

class BasicSafetyMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderPos,
        FIELD_senderPosConfidence,
        FIELD_senderSpeed,
        FIELD_senderSpeedConfidence,
        FIELD_senderHeading,
        FIELD_senderHeadingConfidence,
        FIELD_senderAccel,
        FIELD_senderAccelConfidence,
        FIELD_senderWidth,
        FIELD_senderLength,
        FIELD_senderMbType,
        FIELD_senderAttackType,
        FIELD_senderGpsCoordinates,
        FIELD_senderRealId,
        FIELD_senderPseudonym,
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
    return base ? 15+base->getFieldCount() : 15;
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
        0,    // FIELD_senderPos
        0,    // FIELD_senderPosConfidence
        0,    // FIELD_senderSpeed
        0,    // FIELD_senderSpeedConfidence
        0,    // FIELD_senderHeading
        0,    // FIELD_senderHeadingConfidence
        0,    // FIELD_senderAccel
        0,    // FIELD_senderAccelConfidence
        FD_ISEDITABLE,    // FIELD_senderWidth
        FD_ISEDITABLE,    // FIELD_senderLength
        FD_ISEDITABLE,    // FIELD_senderMbType
        FD_ISEDITABLE,    // FIELD_senderAttackType
        0,    // FIELD_senderGpsCoordinates
        0,    // FIELD_senderRealId
        FD_ISEDITABLE,    // FIELD_senderPseudonym
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
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
        "senderPos",
        "senderPosConfidence",
        "senderSpeed",
        "senderSpeedConfidence",
        "senderHeading",
        "senderHeadingConfidence",
        "senderAccel",
        "senderAccelConfidence",
        "senderWidth",
        "senderLength",
        "senderMbType",
        "senderAttackType",
        "senderGpsCoordinates",
        "senderRealId",
        "senderPseudonym",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int BasicSafetyMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderPos") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "senderPosConfidence") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "senderSpeed") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "senderSpeedConfidence") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "senderHeading") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "senderHeadingConfidence") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "senderAccel") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "senderAccelConfidence") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "senderWidth") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "senderLength") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "senderMbType") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "senderAttackType") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "senderGpsCoordinates") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "senderRealId") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "senderPseudonym") == 0) return baseIndex + 14;
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
        "veins::Coord",    // FIELD_senderPos
        "veins::Coord",    // FIELD_senderPosConfidence
        "veins::Coord",    // FIELD_senderSpeed
        "veins::Coord",    // FIELD_senderSpeedConfidence
        "veins::Coord",    // FIELD_senderHeading
        "veins::Coord",    // FIELD_senderHeadingConfidence
        "veins::Coord",    // FIELD_senderAccel
        "veins::Coord",    // FIELD_senderAccelConfidence
        "double",    // FIELD_senderWidth
        "double",    // FIELD_senderLength
        "int",    // FIELD_senderMbType
        "int",    // FIELD_senderAttackType
        "veins::Coord",    // FIELD_senderGpsCoordinates
        "veins::LAddress::L2Type",    // FIELD_senderRealId
        "unsigned long",    // FIELD_senderPseudonym
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
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
        case FIELD_senderPos: return "";
        case FIELD_senderPosConfidence: return "";
        case FIELD_senderSpeed: return "";
        case FIELD_senderSpeedConfidence: return "";
        case FIELD_senderHeading: return "";
        case FIELD_senderHeadingConfidence: return "";
        case FIELD_senderAccel: return "";
        case FIELD_senderAccelConfidence: return "";
        case FIELD_senderWidth: return double2string(pp->getSenderWidth());
        case FIELD_senderLength: return double2string(pp->getSenderLength());
        case FIELD_senderMbType: return long2string(pp->getSenderMbType());
        case FIELD_senderAttackType: return long2string(pp->getSenderAttackType());
        case FIELD_senderGpsCoordinates: return "";
        case FIELD_senderRealId: return "";
        case FIELD_senderPseudonym: return ulong2string(pp->getSenderPseudonym());
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
        case FIELD_senderWidth: pp->setSenderWidth(string2double(value)); break;
        case FIELD_senderLength: pp->setSenderLength(string2double(value)); break;
        case FIELD_senderMbType: pp->setSenderMbType(string2long(value)); break;
        case FIELD_senderAttackType: pp->setSenderAttackType(string2long(value)); break;
        case FIELD_senderPseudonym: pp->setSenderPseudonym(string2ulong(value)); break;
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
        case FIELD_senderPos: return omnetpp::toAnyPtr(&pp->getSenderPos()); break;
        case FIELD_senderPosConfidence: return omnetpp::toAnyPtr(&pp->getSenderPosConfidence()); break;
        case FIELD_senderSpeed: return omnetpp::toAnyPtr(&pp->getSenderSpeed()); break;
        case FIELD_senderSpeedConfidence: return omnetpp::toAnyPtr(&pp->getSenderSpeedConfidence()); break;
        case FIELD_senderHeading: return omnetpp::toAnyPtr(&pp->getSenderHeading()); break;
        case FIELD_senderHeadingConfidence: return omnetpp::toAnyPtr(&pp->getSenderHeadingConfidence()); break;
        case FIELD_senderAccel: return omnetpp::toAnyPtr(&pp->getSenderAccel()); break;
        case FIELD_senderAccelConfidence: return omnetpp::toAnyPtr(&pp->getSenderAccelConfidence()); break;
        case FIELD_senderWidth: return pp->getSenderWidth();
        case FIELD_senderLength: return pp->getSenderLength();
        case FIELD_senderMbType: return pp->getSenderMbType();
        case FIELD_senderAttackType: return pp->getSenderAttackType();
        case FIELD_senderGpsCoordinates: return omnetpp::toAnyPtr(&pp->getSenderGpsCoordinates()); break;
        case FIELD_senderRealId: return omnetpp::toAnyPtr(&pp->getSenderRealId()); break;
        case FIELD_senderPseudonym: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getSenderPseudonym());
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
        case FIELD_senderWidth: pp->setSenderWidth(value.doubleValue()); break;
        case FIELD_senderLength: pp->setSenderLength(value.doubleValue()); break;
        case FIELD_senderMbType: pp->setSenderMbType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_senderAttackType: pp->setSenderAttackType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_senderPseudonym: pp->setSenderPseudonym(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
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
        case FIELD_senderPos: return omnetpp::toAnyPtr(&pp->getSenderPos()); break;
        case FIELD_senderPosConfidence: return omnetpp::toAnyPtr(&pp->getSenderPosConfidence()); break;
        case FIELD_senderSpeed: return omnetpp::toAnyPtr(&pp->getSenderSpeed()); break;
        case FIELD_senderSpeedConfidence: return omnetpp::toAnyPtr(&pp->getSenderSpeedConfidence()); break;
        case FIELD_senderHeading: return omnetpp::toAnyPtr(&pp->getSenderHeading()); break;
        case FIELD_senderHeadingConfidence: return omnetpp::toAnyPtr(&pp->getSenderHeadingConfidence()); break;
        case FIELD_senderAccel: return omnetpp::toAnyPtr(&pp->getSenderAccel()); break;
        case FIELD_senderAccelConfidence: return omnetpp::toAnyPtr(&pp->getSenderAccelConfidence()); break;
        case FIELD_senderGpsCoordinates: return omnetpp::toAnyPtr(&pp->getSenderGpsCoordinates()); break;
        case FIELD_senderRealId: return omnetpp::toAnyPtr(&pp->getSenderRealId()); break;
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

