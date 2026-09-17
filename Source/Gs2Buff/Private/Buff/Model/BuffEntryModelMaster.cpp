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

#include "Buff/Model/BuffEntryModelMaster.h"

namespace Gs2::Buff::Model
{
    FBuffEntryModelMaster::FBuffEntryModelMaster():
        BuffEntryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ExpressionValue(TOptional<FString>()),
        TargetTypeValue(TOptional<FString>()),
        TargetModelValue(nullptr),
        TargetActionValue(nullptr),
        PriorityValue(TOptional<int32>()),
        ApplyPeriodScheduleEventIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FBuffEntryModelMaster::FBuffEntryModelMaster(
        const FBuffEntryModelMaster& From
    ):
        BuffEntryModelIdValue(From.BuffEntryModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ExpressionValue(From.ExpressionValue),
        TargetTypeValue(From.TargetTypeValue),
        TargetModelValue(From.TargetModelValue),
        TargetActionValue(From.TargetActionValue),
        PriorityValue(From.PriorityValue),
        ApplyPeriodScheduleEventIdValue(From.ApplyPeriodScheduleEventIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithBuffEntryModelId(
        const TOptional<FString> BuffEntryModelId
    )
    {
        this->BuffEntryModelIdValue = BuffEntryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithExpression(
        const TOptional<FString> Expression
    )
    {
        this->ExpressionValue = Expression;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithTargetType(
        const TOptional<FString> TargetType
    )
    {
        this->TargetTypeValue = TargetType;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithTargetModel(
        const TSharedPtr<FBuffTargetModel> TargetModel
    )
    {
        this->TargetModelValue = TargetModel;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithTargetAction(
        const TSharedPtr<FBuffTargetAction> TargetAction
    )
    {
        this->TargetActionValue = TargetAction;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithPriority(
        const TOptional<int32> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithApplyPeriodScheduleEventId(
        const TOptional<FString> ApplyPeriodScheduleEventId
    )
    {
        this->ApplyPeriodScheduleEventIdValue = ApplyPeriodScheduleEventId;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FBuffEntryModelMaster::GetBuffEntryModelId() const
    {
        return BuffEntryModelIdValue;
    }
    TOptional<FString> FBuffEntryModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBuffEntryModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FBuffEntryModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FBuffEntryModelMaster::GetExpression() const
    {
        return ExpressionValue;
    }
    TOptional<FString> FBuffEntryModelMaster::GetTargetType() const
    {
        return TargetTypeValue;
    }
    TSharedPtr<FBuffTargetModel> FBuffEntryModelMaster::GetTargetModel() const
    {
        return TargetModelValue;
    }
    TSharedPtr<FBuffTargetAction> FBuffEntryModelMaster::GetTargetAction() const
    {
        return TargetActionValue;
    }
    TOptional<int32> FBuffEntryModelMaster::GetPriority() const
    {
        return PriorityValue;
    }

    FString FBuffEntryModelMaster::GetPriorityString() const
    {
        if (!PriorityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PriorityValue.GetValue());
    }
    TOptional<FString> FBuffEntryModelMaster::GetApplyPeriodScheduleEventId() const
    {
        return ApplyPeriodScheduleEventIdValue;
    }
    TOptional<int64> FBuffEntryModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FBuffEntryModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FBuffEntryModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FBuffEntryModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FBuffEntryModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FBuffEntryModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FBuffEntryModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModelMaster::GetBuffEntryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBuffEntryModelMaster> FBuffEntryModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBuffEntryModelMaster>()
            ->WithBuffEntryModelId(Data->HasField(ANSI_TO_TCHAR("buffEntryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("buffEntryModelId"), v))
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
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpression(Data->HasField(ANSI_TO_TCHAR("expression")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("expression"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetType(Data->HasField(ANSI_TO_TCHAR("targetType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetModel(Data->HasField(ANSI_TO_TCHAR("targetModel")) ? [Data]() -> Model::FBuffTargetModelPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetModel")))
                    {
                        return nullptr;
                    }
                    return Model::FBuffTargetModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetModel")));
                 }() : nullptr)
            ->WithTargetAction(Data->HasField(ANSI_TO_TCHAR("targetAction")) ? [Data]() -> Model::FBuffTargetActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetAction")))
                    {
                        return nullptr;
                    }
                    return Model::FBuffTargetAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetAction")));
                 }() : nullptr)
            ->WithPriority(Data->HasField(ANSI_TO_TCHAR("priority")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("priority"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithApplyPeriodScheduleEventId(Data->HasField(ANSI_TO_TCHAR("applyPeriodScheduleEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("applyPeriodScheduleEventId"), v))
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

    TSharedPtr<FJsonObject> FBuffEntryModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BuffEntryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("buffEntryModelId"), BuffEntryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("description"), DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (ExpressionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("expression"), ExpressionValue.GetValue());
        }
        if (TargetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("targetType"), TargetTypeValue.GetValue());
        }
        if (TargetModelValue != nullptr && TargetModelValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("targetModel"), TargetModelValue->ToJson());
        }
        if (TargetActionValue != nullptr && TargetActionValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("targetAction"), TargetActionValue->ToJson());
        }
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("priority"), PriorityValue.GetValue());
        }
        if (ApplyPeriodScheduleEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("applyPeriodScheduleEventId"), ApplyPeriodScheduleEventIdValue.GetValue());
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

    FString FBuffEntryModelMaster::TypeName = "BuffEntryModelMaster";
}
#include "Buff/Model/Cache/BuffEntryModelMaster.h"

namespace Gs2::Buff::Model::Cache
{
    FString FBuffEntryModelMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("buff:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":BuffEntryModelMaster");
    }

    FString FBuffEntryModelMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentBuffEntryName
    )
    {
        return
            FString()
            + CacheOwnerArgumentBuffEntryName.Get(FString())
            ;
    }

    bool FBuffEntryModelMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentBuffEntryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Buff::Model::FBuffEntryModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Buff::Model::FBuffEntryModelMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Buff::Model::FBuffEntryModelMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentBuffEntryName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FBuffEntryModelMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentBuffEntryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Buff::Model::FBuffEntryModelMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentBuffEntryName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Buff::Model::FBuffEntryModelMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Buff::Model::FBuffEntryModelMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Buff::Model::FBuffEntryModelMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FBuffEntryModelMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentBuffEntryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Buff::Model::FBuffEntryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentBuffEntryName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentBuffEntryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Buff::Model::FBuffEntryModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Buff::Model::FBuffEntryModelMasterPtr* CacheOwnerArgumentOutItem
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
        Gs2::Buff::Model::FBuffEntryModelMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentBuffEntryName,
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
            CacheOwnerArgumentBuffEntryName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("buffEntryModelMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FBuffEntryModelMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Buff::Model::FBuffEntryModelMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Buff::Model::FBuffEntryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Buff::Model::FBuffEntryModelMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Buff::Model::FBuffEntryModelMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FBuffEntryModelMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Buff::Model::FBuffEntryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}