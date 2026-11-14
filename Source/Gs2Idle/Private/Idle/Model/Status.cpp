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

#include "Idle/Model/Status.h"

namespace Gs2::Idle::Model
{
    FStatus::FStatus():
        StatusIdValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RandomSeedValue(TOptional<int64>()),
        IdleMinutesValue(TOptional<int32>()),
        NextRewardsAtValue(TOptional<int64>()),
        MaximumIdleMinutesValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStatus::FStatus(
        const FStatus& From
    ):
        StatusIdValue(From.StatusIdValue),
        CategoryNameValue(From.CategoryNameValue),
        UserIdValue(From.UserIdValue),
        RandomSeedValue(From.RandomSeedValue),
        IdleMinutesValue(From.IdleMinutesValue),
        NextRewardsAtValue(From.NextRewardsAtValue),
        MaximumIdleMinutesValue(From.MaximumIdleMinutesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStatus> FStatus::WithStatusId(
        const TOptional<FString> StatusId
    )
    {
        this->StatusIdValue = StatusId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithIdleMinutes(
        const TOptional<int32> IdleMinutes
    )
    {
        this->IdleMinutesValue = IdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithNextRewardsAt(
        const TOptional<int64> NextRewardsAt
    )
    {
        this->NextRewardsAtValue = NextRewardsAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithMaximumIdleMinutes(
        const TOptional<int32> MaximumIdleMinutes
    )
    {
        this->MaximumIdleMinutesValue = MaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStatus::GetStatusId() const
    {
        return StatusIdValue;
    }
    TOptional<FString> FStatus::GetCategoryName() const
    {
        return CategoryNameValue;
    }
    TOptional<FString> FStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FStatus::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FStatus::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }
    TOptional<int32> FStatus::GetIdleMinutes() const
    {
        return IdleMinutesValue;
    }

    FString FStatus::GetIdleMinutesString() const
    {
        if (!IdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IdleMinutesValue.GetValue());
    }
    TOptional<int64> FStatus::GetNextRewardsAt() const
    {
        return NextRewardsAtValue;
    }

    FString FStatus::GetNextRewardsAtString() const
    {
        if (!NextRewardsAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRewardsAtValue.GetValue());
    }
    TOptional<int32> FStatus::GetMaximumIdleMinutes() const
    {
        return MaximumIdleMinutesValue;
    }

    FString FStatus::GetMaximumIdleMinutesString() const
    {
        if (!MaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumIdleMinutesValue.GetValue());
    }
    TOptional<int64> FStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStatus::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStatus::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetCategoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStatus> FStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStatus>()
            ->WithStatusId(Data->HasField(ANSI_TO_TCHAR("statusId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("statusId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCategoryName(Data->HasField(ANSI_TO_TCHAR("categoryName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRandomSeed(Data->HasField(ANSI_TO_TCHAR("randomSeed")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("randomSeed"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithIdleMinutes(Data->HasField(ANSI_TO_TCHAR("idleMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("idleMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithNextRewardsAt(Data->HasField(ANSI_TO_TCHAR("nextRewardsAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("nextRewardsAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaximumIdleMinutes(Data->HasField(ANSI_TO_TCHAR("maximumIdleMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumIdleMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
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

    TSharedPtr<FJsonObject> FStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("statusId"), StatusIdValue.GetValue());
        }
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("categoryName"), CategoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (RandomSeedValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("randomSeed"), FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue()));
        }
        if (IdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("idleMinutes"), IdleMinutesValue.GetValue());
        }
        if (NextRewardsAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("nextRewardsAt"), FString::Printf(TEXT("%lld"), NextRewardsAtValue.GetValue()));
        }
        if (MaximumIdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maximumIdleMinutes"), MaximumIdleMinutesValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStatus::TypeName = "Status";
}
#include "Idle/Model/Cache/Status.h"

namespace Gs2::Idle::Model::Cache
{
    FString FStatusCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("idle:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentUserId.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Status");
    }

    FString FStatusCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentCategoryName
    )
    {
        return
            FString()
            + CacheOwnerArgumentCategoryName.Get(FString())
            ;
    }

    bool FStatusCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Idle::Model::FStatusPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!CacheOwnerArgumentUserId.IsSet()) return false;
        Gs2::Idle::Model::FStatusPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Idle::Model::FStatus>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentCategoryName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FStatusCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Idle::Model::FStatusPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentCategoryName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Idle::Model::FStatusPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Idle::Model::FStatus>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Idle::Model::FStatus::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FStatusCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Idle::Model::FStatusPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            UserId,
            Item->GetCategoryName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            UserId,
            TimeOffset
        );
    }

    void FStatusCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        CacheSnapshot->Delete(Gs2::Idle::Model::FStatus::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentCategoryName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Idle::Model::FStatusPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Idle::Model::FStatusPtr* CacheOwnerArgumentOutItem
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
        Gs2::Idle::Model::FStatusPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if ((!CacheOwnerError || CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class)) && !CacheOwnerArgumentUserId.IsSet())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentCategoryName,
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
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentCategoryName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("status"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FStatusCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Idle::Model::FStatusPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Idle::Model::FStatus::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Idle::Model::FStatusPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FStatusCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Idle::Model::FStatus::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}