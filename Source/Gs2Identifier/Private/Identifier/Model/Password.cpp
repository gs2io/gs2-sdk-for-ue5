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

#include "Identifier/Model/Password.h"

namespace Gs2::Identifier::Model
{
    FPassword::FPassword():
        PasswordIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        UserNameValue(TOptional<FString>()),
        EnableTwoFactorAuthenticationValue(TOptional<FString>()),
        TwoFactorAuthenticationSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FPassword::FPassword(
        const FPassword& From
    ):
        PasswordIdValue(From.PasswordIdValue),
        UserIdValue(From.UserIdValue),
        UserNameValue(From.UserNameValue),
        EnableTwoFactorAuthenticationValue(From.EnableTwoFactorAuthenticationValue),
        TwoFactorAuthenticationSettingValue(From.TwoFactorAuthenticationSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FPassword> FPassword::WithPasswordId(
        const TOptional<FString> PasswordId
    )
    {
        this->PasswordIdValue = PasswordId;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithEnableTwoFactorAuthentication(
        const TOptional<FString> EnableTwoFactorAuthentication
    )
    {
        this->EnableTwoFactorAuthenticationValue = EnableTwoFactorAuthentication;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithTwoFactorAuthenticationSetting(
        const TSharedPtr<FTwoFactorAuthenticationSetting> TwoFactorAuthenticationSetting
    )
    {
        this->TwoFactorAuthenticationSettingValue = TwoFactorAuthenticationSetting;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FPassword> FPassword::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FPassword::GetPasswordId() const
    {
        return PasswordIdValue;
    }
    TOptional<FString> FPassword::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FPassword::GetUserName() const
    {
        return UserNameValue;
    }
    TOptional<FString> FPassword::GetEnableTwoFactorAuthentication() const
    {
        return EnableTwoFactorAuthenticationValue;
    }
    TSharedPtr<FTwoFactorAuthenticationSetting> FPassword::GetTwoFactorAuthenticationSetting() const
    {
        return TwoFactorAuthenticationSettingValue;
    }
    TOptional<int64> FPassword::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FPassword::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FPassword::GetRevision() const
    {
        return RevisionValue;
    }

    FString FPassword::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FPassword::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPassword::GetUserNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FPassword> FPassword::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPassword>()
            ->WithPasswordId(Data->HasField(ANSI_TO_TCHAR("passwordId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("passwordId"), v))
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
            ->WithUserName(Data->HasField(ANSI_TO_TCHAR("userName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableTwoFactorAuthentication(Data->HasField(ANSI_TO_TCHAR("enableTwoFactorAuthentication")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("enableTwoFactorAuthentication"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTwoFactorAuthenticationSetting(Data->HasField(ANSI_TO_TCHAR("twoFactorAuthenticationSetting")) ? [Data]() -> Model::FTwoFactorAuthenticationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("twoFactorAuthenticationSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FTwoFactorAuthenticationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("twoFactorAuthenticationSetting")));
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FPassword::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PasswordIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("passwordId"), PasswordIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userName"), UserNameValue.GetValue());
        }
        if (EnableTwoFactorAuthenticationValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("enableTwoFactorAuthentication"), EnableTwoFactorAuthenticationValue.GetValue());
        }
        if (TwoFactorAuthenticationSettingValue != nullptr && TwoFactorAuthenticationSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("twoFactorAuthenticationSetting"), TwoFactorAuthenticationSettingValue->ToJson());
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

    FString FPassword::TypeName = "Password";
}
#include "Identifier/Model/Cache/Password.h"

namespace Gs2::Identifier::Model::Cache
{
    FString FPasswordCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("identifier:")
            + CacheOwnerArgumentUserName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Password");
    }

    FString FPasswordCache::CreateCacheKey(
    )
    {
        return FString("Singleton");
    }

    bool FPasswordCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Identifier::Model::FPasswordPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Identifier::Model::FPasswordPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Identifier::Model::FPassword>(
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

    void FPasswordCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Identifier::Model::FPasswordPtr& CacheOwnerArgumentItem
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
        Gs2::Identifier::Model::FPasswordPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Identifier::Model::FPassword>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Identifier::Model::FPassword::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FPasswordCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Identifier::Model::FPasswordPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            Item->GetUserName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            Item->GetUserName(),
            TimeOffset
        );
    }

    void FPasswordCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Identifier::Model::FPassword::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Identifier::Model::FPasswordPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Identifier::Model::FPasswordPtr* CacheOwnerArgumentOutItem
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
        Gs2::Identifier::Model::FPasswordPtr CacheOwnerFetchedItem;
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
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("password"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FPasswordCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Identifier::Model::FPasswordPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Identifier::Model::FPassword::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Identifier::Model::FPasswordPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Identifier::Model::FPassword>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FPasswordCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentUserName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Identifier::Model::FPassword::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentUserName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}