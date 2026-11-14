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

#include "Stamina/Model/Stamina.h"

namespace Gs2::Stamina::Model
{
    FStamina::FStamina():
        StaminaIdValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ValueValue(TOptional<int32>()),
        MaxValueValue(TOptional<int32>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        OverflowValueValue(TOptional<int32>()),
        NextRecoverAtValue(TOptional<int64>()),
        LastRecoveredAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStamina::FStamina(
        const FStamina& From
    ):
        StaminaIdValue(From.StaminaIdValue),
        StaminaNameValue(From.StaminaNameValue),
        UserIdValue(From.UserIdValue),
        ValueValue(From.ValueValue),
        MaxValueValue(From.MaxValueValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        OverflowValueValue(From.OverflowValueValue),
        NextRecoverAtValue(From.NextRecoverAtValue),
        LastRecoveredAtValue(From.LastRecoveredAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStamina> FStamina::WithStaminaId(
        const TOptional<FString> StaminaId
    )
    {
        this->StaminaIdValue = StaminaId;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithMaxValue(
        const TOptional<int32> MaxValue
    )
    {
        this->MaxValueValue = MaxValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithOverflowValue(
        const TOptional<int32> OverflowValue
    )
    {
        this->OverflowValueValue = OverflowValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithNextRecoverAt(
        const TOptional<int64> NextRecoverAt
    )
    {
        this->NextRecoverAtValue = NextRecoverAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithLastRecoveredAt(
        const TOptional<int64> LastRecoveredAt
    )
    {
        this->LastRecoveredAtValue = LastRecoveredAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStamina::GetStaminaId() const
    {
        return StaminaIdValue;
    }
    TOptional<FString> FStamina::GetStaminaName() const
    {
        return StaminaNameValue;
    }
    TOptional<FString> FStamina::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FStamina::GetValue() const
    {
        return ValueValue;
    }

    FString FStamina::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetMaxValue() const
    {
        return MaxValueValue;
    }

    FString FStamina::GetMaxValueString() const
    {
        if (!MaxValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FStamina::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FStamina::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FStamina::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetOverflowValue() const
    {
        return OverflowValueValue;
    }

    FString FStamina::GetOverflowValueString() const
    {
        if (!OverflowValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), OverflowValueValue.GetValue());
    }
    TOptional<int64> FStamina::GetNextRecoverAt() const
    {
        return NextRecoverAtValue;
    }

    FString FStamina::GetNextRecoverAtString() const
    {
        if (!NextRecoverAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRecoverAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetLastRecoveredAt() const
    {
        return LastRecoveredAtValue;
    }

    FString FStamina::GetLastRecoveredAtString() const
    {
        if (!LastRecoveredAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastRecoveredAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStamina::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStamina::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStamina::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStamina::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetStaminaNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStamina> FStamina::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStamina>()
            ->WithStaminaId(Data->HasField(ANSI_TO_TCHAR("staminaId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("staminaId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStaminaName(Data->HasField(ANSI_TO_TCHAR("staminaName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("staminaName"), v))
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
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxValue(Data->HasField(ANSI_TO_TCHAR("maxValue")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecoverIntervalMinutes(Data->HasField(ANSI_TO_TCHAR("recoverIntervalMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("recoverIntervalMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecoverValue(Data->HasField(ANSI_TO_TCHAR("recoverValue")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("recoverValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithOverflowValue(Data->HasField(ANSI_TO_TCHAR("overflowValue")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("overflowValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithNextRecoverAt(Data->HasField(ANSI_TO_TCHAR("nextRecoverAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("nextRecoverAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastRecoveredAt(Data->HasField(ANSI_TO_TCHAR("lastRecoveredAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lastRecoveredAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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

    TSharedPtr<FJsonObject> FStamina::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StaminaIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("staminaId"), StaminaIdValue.GetValue());
        }
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("staminaName"), StaminaNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("value"), ValueValue.GetValue());
        }
        if (MaxValueValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maxValue"), MaxValueValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("recoverIntervalMinutes"), RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("recoverValue"), RecoverValueValue.GetValue());
        }
        if (OverflowValueValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("overflowValue"), OverflowValueValue.GetValue());
        }
        if (NextRecoverAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("nextRecoverAt"), FString::Printf(TEXT("%lld"), NextRecoverAtValue.GetValue()));
        }
        if (LastRecoveredAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("lastRecoveredAt"), FString::Printf(TEXT("%lld"), LastRecoveredAtValue.GetValue()));
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

    FString FStamina::TypeName = "Stamina";
}
#include "Stamina/Model/Cache/Stamina.h"

namespace Gs2::Stamina::Model::Cache
{
    FString FStaminaCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("stamina:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentUserId.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Stamina");
    }

    FString FStaminaCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentStaminaName
    )
    {
        return
            FString()
            + CacheOwnerArgumentStaminaName.Get(FString())
            ;
    }

    bool FStaminaCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Stamina::Model::FStaminaPtr* CacheOwnerArgumentOutItem
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
        Gs2::Stamina::Model::FStaminaPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Stamina::Model::FStamina>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentStaminaName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FStaminaCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Stamina::Model::FStaminaPtr& CacheOwnerArgumentItem
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
            CacheOwnerArgumentStaminaName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Stamina::Model::FStaminaPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Stamina::Model::FStamina>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Stamina::Model::FStamina::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FStaminaCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Stamina::Model::FStaminaPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            UserId,
            Item->GetStaminaName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            UserId,
            TimeOffset
        );
    }

    void FStaminaCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        CacheSnapshot->Delete(Gs2::Stamina::Model::FStamina::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentStaminaName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Stamina::Model::FStaminaPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Stamina::Model::FStaminaPtr* CacheOwnerArgumentOutItem
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
        Gs2::Stamina::Model::FStaminaPtr CacheOwnerFetchedItem;
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
                CacheOwnerArgumentStaminaName,
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
            CacheOwnerArgumentStaminaName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("stamina"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FStaminaCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Stamina::Model::FStaminaPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Stamina::Model::FStamina::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Stamina::Model::FStaminaPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FStamina>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FStaminaCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Stamina::Model::FStamina::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}