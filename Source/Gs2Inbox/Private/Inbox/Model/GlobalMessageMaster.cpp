/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Inbox/Model/GlobalMessageMaster.h"

namespace Gs2::Inbox::Model
{
    FGlobalMessageMaster::FGlobalMessageMaster():
        GlobalMessageIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReadAcquireActionsValue(nullptr),
        ExpiresTimeSpanValue(nullptr),
        ExpiresAtValue(TOptional<int64>()),
        MessageReceptionPeriodEventIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGlobalMessageMaster::FGlobalMessageMaster(
        const FGlobalMessageMaster& From
    ):
        GlobalMessageIdValue(From.GlobalMessageIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ExpiresTimeSpanValue(From.ExpiresTimeSpanValue),
        ExpiresAtValue(From.ExpiresAtValue),
        MessageReceptionPeriodEventIdValue(From.MessageReceptionPeriodEventIdValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithGlobalMessageId(
        const TOptional<FString> GlobalMessageId
    )
    {
        this->GlobalMessageIdValue = GlobalMessageId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithExpiresTimeSpan(
        const TSharedPtr<FTimeSpan> ExpiresTimeSpan
    )
    {
        this->ExpiresTimeSpanValue = ExpiresTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithMessageReceptionPeriodEventId(
        const TOptional<FString> MessageReceptionPeriodEventId
    )
    {
        this->MessageReceptionPeriodEventIdValue = MessageReceptionPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGlobalMessageMaster::GetGlobalMessageId() const
    {
        return GlobalMessageIdValue;
    }
    TOptional<FString> FGlobalMessageMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGlobalMessageMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FGlobalMessageMaster::GetReadAcquireActions() const
    {
        return ReadAcquireActionsValue;
    }
    TSharedPtr<FTimeSpan> FGlobalMessageMaster::GetExpiresTimeSpan() const
    {
        return ExpiresTimeSpanValue;
    }
    TOptional<int64> FGlobalMessageMaster::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FGlobalMessageMaster::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TOptional<FString> FGlobalMessageMaster::GetMessageReceptionPeriodEventId() const
    {
        return MessageReceptionPeriodEventIdValue;
    }
    TOptional<int64> FGlobalMessageMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FGlobalMessageMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FGlobalMessageMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGlobalMessageMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGlobalMessageMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):master:globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessageMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):master:globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessageMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):master:globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalMessageMaster::GetGlobalMessageNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inbox:(?<namespaceName>.+):master:globalMessage:(?<globalMessageName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGlobalMessageMaster> FGlobalMessageMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalMessageMaster>()
            ->WithGlobalMessageId(Data->HasField(ANSI_TO_TCHAR("globalMessageId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalMessageId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReadAcquireActions(Data->HasField(ANSI_TO_TCHAR("readAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("readAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("readAcquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("readAcquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithExpiresTimeSpan(Data->HasField(ANSI_TO_TCHAR("expiresTimeSpan")) ? [Data]() -> Model::FTimeSpanPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("expiresTimeSpan")))
                    {
                        return nullptr;
                    }
                    return Model::FTimeSpan::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("expiresTimeSpan")));
                 }() : nullptr)
            ->WithExpiresAt(Data->HasField(ANSI_TO_TCHAR("expiresAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expiresAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMessageReceptionPeriodEventId(Data->HasField(ANSI_TO_TCHAR("messageReceptionPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("messageReceptionPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FGlobalMessageMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GlobalMessageIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("globalMessageId"), GlobalMessageIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (ReadAcquireActionsValue != nullptr && ReadAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReadAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("readAcquireActions"), v);
        }
        if (ExpiresTimeSpanValue != nullptr && ExpiresTimeSpanValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("expiresTimeSpan"), ExpiresTimeSpanValue->ToJson());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("expiresAt"), FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (MessageReceptionPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("messageReceptionPeriodEventId"), MessageReceptionPeriodEventIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGlobalMessageMaster::TypeName = "GlobalMessageMaster";
}
#include "Inbox/Model/Cache/GlobalMessageMaster.h"

namespace Gs2::Inbox::Model::Cache
{
    FString FGlobalMessageMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("inbox:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":GlobalMessageMaster");
    }

    FString FGlobalMessageMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentGlobalMessageName
    )
    {
        return
            FString()
            + CacheOwnerArgumentGlobalMessageName.Get(FString())
            ;
    }

    bool FGlobalMessageMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGlobalMessageName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Inbox::Model::FGlobalMessageMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Inbox::Model::FGlobalMessageMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentGlobalMessageName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FGlobalMessageMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGlobalMessageName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Inbox::Model::FGlobalMessageMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentGlobalMessageName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Inbox::Model::FGlobalMessageMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Inbox::Model::FGlobalMessageMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Inbox::Model::FGlobalMessageMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            CacheOwnerValue.IsValid() && CacheOwnerValue->GetExpiresAt().IsSet() && CacheOwnerValue->GetExpiresAt().Get(0) != 0
                ? FDateTime::FromUnixTimestamp(0) + FTimespan::FromMilliseconds(CacheOwnerValue->GetExpiresAt().Get(0))
                : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FGlobalMessageMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGlobalMessageName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Inbox::Model::FGlobalMessageMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentGlobalMessageName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGlobalMessageName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Inbox::Model::FGlobalMessageMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Inbox::Model::FGlobalMessageMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Inbox::Model::FGlobalMessageMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentGlobalMessageName,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentGlobalMessageName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("globalMessageMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FGlobalMessageMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Inbox::Model::FGlobalMessageMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Inbox::Model::FGlobalMessageMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Inbox::Model::FGlobalMessageMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FGlobalMessageMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Inbox::Model::FGlobalMessageMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}