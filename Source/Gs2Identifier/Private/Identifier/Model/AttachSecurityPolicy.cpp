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

#include "Identifier/Model/AttachSecurityPolicy.h"

namespace Gs2::Identifier::Model
{
    FAttachSecurityPolicy::FAttachSecurityPolicy():
        UserIdValue(TOptional<FString>()),
        SecurityPolicyIdsValue(nullptr),
        AttachedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FAttachSecurityPolicy::FAttachSecurityPolicy(
        const FAttachSecurityPolicy& From
    ):
        UserIdValue(From.UserIdValue),
        SecurityPolicyIdsValue(From.SecurityPolicyIdsValue),
        AttachedAtValue(From.AttachedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithSecurityPolicyIds(
        const TSharedPtr<TArray<FString>> SecurityPolicyIds
    )
    {
        this->SecurityPolicyIdsValue = SecurityPolicyIds;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithAttachedAt(
        const TOptional<int64> AttachedAt
    )
    {
        this->AttachedAtValue = AttachedAt;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FAttachSecurityPolicy::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<FString>> FAttachSecurityPolicy::GetSecurityPolicyIds() const
    {
        return SecurityPolicyIdsValue;
    }
    TOptional<int64> FAttachSecurityPolicy::GetAttachedAt() const
    {
        return AttachedAtValue;
    }

    FString FAttachSecurityPolicy::GetAttachedAtString() const
    {
        if (!AttachedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AttachedAtValue.GetValue());
    }
    TOptional<int64> FAttachSecurityPolicy::GetRevision() const
    {
        return RevisionValue;
    }

    FString FAttachSecurityPolicy::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FAttachSecurityPolicy::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAttachSecurityPolicy::GetUserNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttachSecurityPolicy>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSecurityPolicyIds(Data->HasField(ANSI_TO_TCHAR("securityPolicyIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("securityPolicyIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("securityPolicyIds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("securityPolicyIds")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithAttachedAt(Data->HasField(ANSI_TO_TCHAR("attachedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attachedAt"), v))
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

    TSharedPtr<FJsonObject> FAttachSecurityPolicy::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (SecurityPolicyIdsValue != nullptr && SecurityPolicyIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SecurityPolicyIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("securityPolicyIds"), v);
        }
        if (AttachedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("attachedAt"), FString::Printf(TEXT("%lld"), AttachedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FAttachSecurityPolicy::TypeName = "AttachSecurityPolicy";
}
#include "Identifier/Model/Cache/AttachSecurityPolicy.h"

namespace Gs2::Identifier::Model::Cache
{
    FString FAttachSecurityPolicyCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("identifier:")
            + CacheOwnerArgumentUserName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":AttachSecurityPolicy");
    }

    FString FAttachSecurityPolicyCache::CreateCacheKey(
    )
    {
        return FString("Singleton");
    }

    bool FAttachSecurityPolicyCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Identifier::Model::FAttachSecurityPolicyPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Identifier::Model::FAttachSecurityPolicyPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Identifier::Model::FAttachSecurityPolicy>(
            CreateCacheParentKey(
                CacheOwnerArgumentUserName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FAttachSecurityPolicyCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Identifier::Model::FAttachSecurityPolicyPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Identifier::Model::FAttachSecurityPolicyPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Identifier::Model::FAttachSecurityPolicy>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FAttachSecurityPolicyCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Identifier::Model::FAttachSecurityPolicyPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Identifier::Model::FAttachSecurityPolicyPtr* CacheOwnerArgumentOutItem
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
        Gs2::Identifier::Model::FAttachSecurityPolicyPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentUserName,
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
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("attachSecurityPolicy"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FAttachSecurityPolicyCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Identifier::Model::FAttachSecurityPolicyPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Identifier::Model::FAttachSecurityPolicyPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FAttachSecurityPolicyCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}