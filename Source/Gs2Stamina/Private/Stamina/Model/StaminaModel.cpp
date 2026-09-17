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

#include "Stamina/Model/StaminaModel.h"

namespace Gs2::Stamina::Model
{
    FStaminaModel::FStaminaModel():
        StaminaModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        InitialCapacityValue(TOptional<int32>()),
        IsOverflowValue(TOptional<bool>()),
        MaxCapacityValue(TOptional<int32>()),
        MaxStaminaTableValue(nullptr),
        RecoverIntervalTableValue(nullptr),
        RecoverValueTableValue(nullptr)
    {
    }

    FStaminaModel::FStaminaModel(
        const FStaminaModel& From
    ):
        StaminaModelIdValue(From.StaminaModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        InitialCapacityValue(From.InitialCapacityValue),
        IsOverflowValue(From.IsOverflowValue),
        MaxCapacityValue(From.MaxCapacityValue),
        MaxStaminaTableValue(From.MaxStaminaTableValue),
        RecoverIntervalTableValue(From.RecoverIntervalTableValue),
        RecoverValueTableValue(From.RecoverValueTableValue)
    {
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithStaminaModelId(
        const TOptional<FString> StaminaModelId
    )
    {
        this->StaminaModelIdValue = StaminaModelId;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithIsOverflow(
        const TOptional<bool> IsOverflow
    )
    {
        this->IsOverflowValue = IsOverflow;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMaxStaminaTable(
        const TSharedPtr<FMaxStaminaTable> MaxStaminaTable
    )
    {
        this->MaxStaminaTableValue = MaxStaminaTable;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverIntervalTable(
        const TSharedPtr<FRecoverIntervalTable> RecoverIntervalTable
    )
    {
        this->RecoverIntervalTableValue = RecoverIntervalTable;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverValueTable(
        const TSharedPtr<FRecoverValueTable> RecoverValueTable
    )
    {
        this->RecoverValueTableValue = RecoverValueTable;
        return SharedThis(this);
    }
    TOptional<FString> FStaminaModel::GetStaminaModelId() const
    {
        return StaminaModelIdValue;
    }
    TOptional<FString> FStaminaModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FStaminaModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FStaminaModel::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FStaminaModel::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FStaminaModel::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FStaminaModel::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FStaminaModel::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FStaminaModel::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<bool> FStaminaModel::GetIsOverflow() const
    {
        return IsOverflowValue;
    }

    FString FStaminaModel::GetIsOverflowString() const
    {
        if (!IsOverflowValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsOverflowValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FStaminaModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FStaminaModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TSharedPtr<FMaxStaminaTable> FStaminaModel::GetMaxStaminaTable() const
    {
        return MaxStaminaTableValue;
    }
    TSharedPtr<FRecoverIntervalTable> FStaminaModel::GetRecoverIntervalTable() const
    {
        return RecoverIntervalTableValue;
    }
    TSharedPtr<FRecoverValueTable> FStaminaModel::GetRecoverValueTable() const
    {
        return RecoverValueTableValue;
    }

    TOptional<FString> FStaminaModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetStaminaNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStaminaModel> FStaminaModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStaminaModel>()
            ->WithStaminaModelId(Data->HasField(ANSI_TO_TCHAR("staminaModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("staminaModelId"), v))
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
            ->WithInitialCapacity(Data->HasField(ANSI_TO_TCHAR("initialCapacity")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("initialCapacity"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithIsOverflow(Data->HasField(ANSI_TO_TCHAR("isOverflow")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("isOverflow"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithMaxCapacity(Data->HasField(ANSI_TO_TCHAR("maxCapacity")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxCapacity"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxStaminaTable(Data->HasField(ANSI_TO_TCHAR("maxStaminaTable")) ? [Data]() -> Model::FMaxStaminaTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("maxStaminaTable")))
                    {
                        return nullptr;
                    }
                    return Model::FMaxStaminaTable::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("maxStaminaTable")));
                 }() : nullptr)
            ->WithRecoverIntervalTable(Data->HasField(ANSI_TO_TCHAR("recoverIntervalTable")) ? [Data]() -> Model::FRecoverIntervalTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("recoverIntervalTable")))
                    {
                        return nullptr;
                    }
                    return Model::FRecoverIntervalTable::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("recoverIntervalTable")));
                 }() : nullptr)
            ->WithRecoverValueTable(Data->HasField(ANSI_TO_TCHAR("recoverValueTable")) ? [Data]() -> Model::FRecoverValueTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("recoverValueTable")))
                    {
                        return nullptr;
                    }
                    return Model::FRecoverValueTable::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("recoverValueTable")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FStaminaModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StaminaModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("staminaModelId"), StaminaModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("recoverIntervalMinutes"), RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("recoverValue"), RecoverValueValue.GetValue());
        }
        if (InitialCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("initialCapacity"), InitialCapacityValue.GetValue());
        }
        if (IsOverflowValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("isOverflow"), IsOverflowValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maxCapacity"), MaxCapacityValue.GetValue());
        }
        if (MaxStaminaTableValue != nullptr && MaxStaminaTableValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("maxStaminaTable"), MaxStaminaTableValue->ToJson());
        }
        if (RecoverIntervalTableValue != nullptr && RecoverIntervalTableValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("recoverIntervalTable"), RecoverIntervalTableValue->ToJson());
        }
        if (RecoverValueTableValue != nullptr && RecoverValueTableValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("recoverValueTable"), RecoverValueTableValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FStaminaModel::TypeName = "StaminaModel";
}
#include "Stamina/Model/Cache/StaminaModel.h"

namespace Gs2::Stamina::Model::Cache
{
    FString FStaminaModelCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("stamina:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":StaminaModel");
    }

    FString FStaminaModelCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentStaminaName
    )
    {
        return
            FString()
            + CacheOwnerArgumentStaminaName.Get(FString())
            ;
    }

    bool FStaminaModelCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Stamina::Model::FStaminaModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Stamina::Model::FStaminaModelPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Stamina::Model::FStaminaModel>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
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

    void FStaminaModelCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Stamina::Model::FStaminaModelPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentStaminaName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Stamina::Model::FStaminaModel::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FStaminaModelCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Stamina::Model::FStaminaModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentStaminaName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaModelCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentStaminaName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Stamina::Model::FStaminaModelPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Stamina::Model::FStaminaModelPtr* CacheOwnerArgumentOutItem
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
        Gs2::Stamina::Model::FStaminaModelPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
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
            CacheOwnerArgumentStaminaName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("staminaModel"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FStaminaModelCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Stamina::Model::FStaminaModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Stamina::Model::FStaminaModelPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FStaminaModel>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FStaminaModelCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Stamina::Model::FStaminaModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}