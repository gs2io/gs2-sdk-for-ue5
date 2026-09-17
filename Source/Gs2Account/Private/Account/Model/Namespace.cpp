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

#include "Account/Model/Namespace.h"

namespace Gs2::Account::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        TransactionSettingV2Value(nullptr),
        ChangePasswordIfTakeOverValue(TOptional<bool>()),
        DifferentUserIdForLoginAndDataRetentionValue(TOptional<bool>()),
        CreateAccountScriptValue(nullptr),
        AuthenticationScriptValue(nullptr),
        CreateTakeOverScriptValue(nullptr),
        DoTakeOverScriptValue(nullptr),
        BanScriptValue(nullptr),
        UnBanScriptValue(nullptr),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        TransactionSettingV2Value(From.TransactionSettingV2Value),
        ChangePasswordIfTakeOverValue(From.ChangePasswordIfTakeOverValue),
        DifferentUserIdForLoginAndDataRetentionValue(From.DifferentUserIdForLoginAndDataRetentionValue),
        CreateAccountScriptValue(From.CreateAccountScriptValue),
        AuthenticationScriptValue(From.AuthenticationScriptValue),
        CreateTakeOverScriptValue(From.CreateTakeOverScriptValue),
        DoTakeOverScriptValue(From.DoTakeOverScriptValue),
        BanScriptValue(From.BanScriptValue),
        UnBanScriptValue(From.UnBanScriptValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTransactionSetting(
        const TSharedPtr<FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTransactionSettingV2(
        const TSharedPtr<FTransactionSettingV2> TransactionSettingV2
    )
    {
        this->TransactionSettingV2Value = TransactionSettingV2;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangePasswordIfTakeOver(
        const TOptional<bool> ChangePasswordIfTakeOver
    )
    {
        this->ChangePasswordIfTakeOverValue = ChangePasswordIfTakeOver;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDifferentUserIdForLoginAndDataRetention(
        const TOptional<bool> DifferentUserIdForLoginAndDataRetention
    )
    {
        this->DifferentUserIdForLoginAndDataRetentionValue = DifferentUserIdForLoginAndDataRetention;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateAccountScript(
        const TSharedPtr<FScriptSetting> CreateAccountScript
    )
    {
        this->CreateAccountScriptValue = CreateAccountScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAuthenticationScript(
        const TSharedPtr<FScriptSetting> AuthenticationScript
    )
    {
        this->AuthenticationScriptValue = AuthenticationScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateTakeOverScript(
        const TSharedPtr<FScriptSetting> CreateTakeOverScript
    )
    {
        this->CreateTakeOverScriptValue = CreateTakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDoTakeOverScript(
        const TSharedPtr<FScriptSetting> DoTakeOverScript
    )
    {
        this->DoTakeOverScriptValue = DoTakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithBanScript(
        const TSharedPtr<FScriptSetting> BanScript
    )
    {
        this->BanScriptValue = BanScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUnBanScript(
        const TSharedPtr<FScriptSetting> UnBanScript
    )
    {
        this->UnBanScriptValue = UnBanScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogSetting(
        const TSharedPtr<FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TSharedPtr<FTransactionSetting> FNamespace::GetTransactionSetting() const
    {
        return TransactionSettingValue;
    }
    TSharedPtr<FTransactionSettingV2> FNamespace::GetTransactionSettingV2() const
    {
        return TransactionSettingV2Value;
    }
    TOptional<bool> FNamespace::GetChangePasswordIfTakeOver() const
    {
        return ChangePasswordIfTakeOverValue;
    }

    FString FNamespace::GetChangePasswordIfTakeOverString() const
    {
        if (!ChangePasswordIfTakeOverValue.IsSet())
        {
            return FString("null");
        }
        return FString(ChangePasswordIfTakeOverValue.GetValue() ? "true" : "false");
    }
    TOptional<bool> FNamespace::GetDifferentUserIdForLoginAndDataRetention() const
    {
        return DifferentUserIdForLoginAndDataRetentionValue;
    }

    FString FNamespace::GetDifferentUserIdForLoginAndDataRetentionString() const
    {
        if (!DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            return FString("null");
        }
        return FString(DifferentUserIdForLoginAndDataRetentionValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateAccountScript() const
    {
        return CreateAccountScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetAuthenticationScript() const
    {
        return AuthenticationScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateTakeOverScript() const
    {
        return CreateTakeOverScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDoTakeOverScript() const
    {
        return DoTakeOverScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetBanScript() const
    {
        return BanScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetUnBanScript() const
    {
        return UnBanScriptValue;
    }
    TSharedPtr<FLogSetting> FNamespace::GetLogSetting() const
    {
        return LogSettingValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
                 }() : nullptr)
            ->WithTransactionSettingV2(Data->HasField(ANSI_TO_TCHAR("transactionSettingV2")) ? [Data]() -> Model::FTransactionSettingV2Ptr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSettingV2")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSettingV2::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSettingV2")));
                 }() : nullptr)
            ->WithChangePasswordIfTakeOver(Data->HasField(ANSI_TO_TCHAR("changePasswordIfTakeOver")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("changePasswordIfTakeOver"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithDifferentUserIdForLoginAndDataRetention(Data->HasField(ANSI_TO_TCHAR("differentUserIdForLoginAndDataRetention")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("differentUserIdForLoginAndDataRetention"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCreateAccountScript(Data->HasField(ANSI_TO_TCHAR("createAccountScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createAccountScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createAccountScript")));
                 }() : nullptr)
            ->WithAuthenticationScript(Data->HasField(ANSI_TO_TCHAR("authenticationScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("authenticationScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("authenticationScript")));
                 }() : nullptr)
            ->WithCreateTakeOverScript(Data->HasField(ANSI_TO_TCHAR("createTakeOverScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createTakeOverScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createTakeOverScript")));
                 }() : nullptr)
            ->WithDoTakeOverScript(Data->HasField(ANSI_TO_TCHAR("doTakeOverScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("doTakeOverScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("doTakeOverScript")));
                 }() : nullptr)
            ->WithBanScript(Data->HasField(ANSI_TO_TCHAR("banScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("banScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("banScript")));
                 }() : nullptr)
            ->WithUnBanScript(Data->HasField(ANSI_TO_TCHAR("unBanScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unBanScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unBanScript")));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
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

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceId"), NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("description"), DescriptionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("transactionSetting"), TransactionSettingValue->ToJson());
        }
        if (TransactionSettingV2Value != nullptr && TransactionSettingV2Value.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("transactionSettingV2"), TransactionSettingV2Value->ToJson());
        }
        if (ChangePasswordIfTakeOverValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("changePasswordIfTakeOver"), ChangePasswordIfTakeOverValue.GetValue());
        }
        if (DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("differentUserIdForLoginAndDataRetention"), DifferentUserIdForLoginAndDataRetentionValue.GetValue());
        }
        if (CreateAccountScriptValue != nullptr && CreateAccountScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("createAccountScript"), CreateAccountScriptValue->ToJson());
        }
        if (AuthenticationScriptValue != nullptr && AuthenticationScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("authenticationScript"), AuthenticationScriptValue->ToJson());
        }
        if (CreateTakeOverScriptValue != nullptr && CreateTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("createTakeOverScript"), CreateTakeOverScriptValue->ToJson());
        }
        if (DoTakeOverScriptValue != nullptr && DoTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("doTakeOverScript"), DoTakeOverScriptValue->ToJson());
        }
        if (BanScriptValue != nullptr && BanScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("banScript"), BanScriptValue->ToJson());
        }
        if (UnBanScriptValue != nullptr && UnBanScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("unBanScript"), UnBanScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("logSetting"), LogSettingValue->ToJson());
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

    FString FNamespace::TypeName = "Namespace";
}
#include "Account/Model/Cache/Namespace.h"

namespace Gs2::Account::Model::Cache
{
    FString FNamespaceCache::CreateCacheParentKey(
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("account:")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Namespace");
    }

    FString FNamespaceCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName
    )
    {
        return
            FString()
            + CacheOwnerArgumentNamespaceName.Get(FString())
            ;
    }

    bool FNamespaceCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Account::Model::FNamespacePtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Account::Model::FNamespacePtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Account::Model::FNamespace>(
            CreateCacheParentKey(
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentNamespaceName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FNamespaceCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Account::Model::FNamespacePtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentNamespaceName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Account::Model::FNamespacePtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Account::Model::FNamespace>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Account::Model::FNamespace::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FNamespaceCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Account::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentNamespaceName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Account::Model::FNamespacePtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Account::Model::FNamespacePtr* CacheOwnerArgumentOutItem
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
        Gs2::Account::Model::FNamespacePtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
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
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("namespace"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FNamespaceCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Account::Model::FNamespacePtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Account::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Account::Model::FNamespacePtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FNamespace>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FNamespaceCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Account::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}