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

#include "Mission/Model/MissionTaskModel.h"

namespace Gs2::Mission::Model
{
    FMissionTaskModel::FMissionTaskModel():
        MissionTaskIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        VerifyCompleteTypeValue(TOptional<FString>()),
        TargetCounterValue(nullptr),
        VerifyCompleteConsumeActionsValue(nullptr),
        CompleteAcquireActionsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        PremiseMissionTaskNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        TargetResetTypeValue(TOptional<FString>()),
        TargetValueValue(TOptional<int64>())
    {
    }

    FMissionTaskModel::FMissionTaskModel(
        const FMissionTaskModel& From
    ):
        MissionTaskIdValue(From.MissionTaskIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        VerifyCompleteTypeValue(From.VerifyCompleteTypeValue),
        TargetCounterValue(From.TargetCounterValue),
        VerifyCompleteConsumeActionsValue(From.VerifyCompleteConsumeActionsValue),
        CompleteAcquireActionsValue(From.CompleteAcquireActionsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        PremiseMissionTaskNameValue(From.PremiseMissionTaskNameValue),
        CounterNameValue(From.CounterNameValue),
        TargetResetTypeValue(From.TargetResetTypeValue),
        TargetValueValue(From.TargetValueValue)
    {
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithMissionTaskId(
        const TOptional<FString> MissionTaskId
    )
    {
        this->MissionTaskIdValue = MissionTaskId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithVerifyCompleteType(
        const TOptional<FString> VerifyCompleteType
    )
    {
        this->VerifyCompleteTypeValue = VerifyCompleteType;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithTargetCounter(
        const TSharedPtr<FTargetCounterModel> TargetCounter
    )
    {
        this->TargetCounterValue = TargetCounter;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithVerifyCompleteConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyCompleteConsumeActions
    )
    {
        this->VerifyCompleteConsumeActionsValue = VerifyCompleteConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithPremiseMissionTaskName(
        const TOptional<FString> PremiseMissionTaskName
    )
    {
        this->PremiseMissionTaskNameValue = PremiseMissionTaskName;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithTargetResetType(
        const TOptional<FString> TargetResetType
    )
    {
        this->TargetResetTypeValue = TargetResetType;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithTargetValue(
        const TOptional<int64> TargetValue
    )
    {
        this->TargetValueValue = TargetValue;
        return SharedThis(this);
    }
    TOptional<FString> FMissionTaskModel::GetMissionTaskId() const
    {
        return MissionTaskIdValue;
    }
    TOptional<FString> FMissionTaskModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMissionTaskModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FMissionTaskModel::GetVerifyCompleteType() const
    {
        return VerifyCompleteTypeValue;
    }
    TSharedPtr<FTargetCounterModel> FMissionTaskModel::GetTargetCounter() const
    {
        return TargetCounterValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FMissionTaskModel::GetVerifyCompleteConsumeActions() const
    {
        return VerifyCompleteConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FMissionTaskModel::GetCompleteAcquireActions() const
    {
        return CompleteAcquireActionsValue;
    }
    TOptional<FString> FMissionTaskModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TOptional<FString> FMissionTaskModel::GetPremiseMissionTaskName() const
    {
        return PremiseMissionTaskNameValue;
    }
    TOptional<FString> FMissionTaskModel::GetCounterName() const
    {
        return CounterNameValue;
    }
    TOptional<FString> FMissionTaskModel::GetTargetResetType() const
    {
        return TargetResetTypeValue;
    }
    TOptional<int64> FMissionTaskModel::GetTargetValue() const
    {
        return TargetValueValue;
    }

    FString FMissionTaskModel::GetTargetValueString() const
    {
        if (!TargetValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetValueValue.GetValue());
    }

    TOptional<FString> FMissionTaskModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetMissionGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetMissionTaskNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMissionTaskModel>()
            ->WithMissionTaskId(Data->HasField(ANSI_TO_TCHAR("missionTaskId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missionTaskId"), v))
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
            ->WithVerifyCompleteType(Data->HasField(ANSI_TO_TCHAR("verifyCompleteType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyCompleteType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetCounter(Data->HasField(ANSI_TO_TCHAR("targetCounter")) ? [Data]() -> Model::FTargetCounterModelPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetCounter")))
                    {
                        return nullptr;
                    }
                    return Model::FTargetCounterModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetCounter")));
                 }() : nullptr)
            ->WithVerifyCompleteConsumeActions(Data->HasField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                        {
                            v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
            ->WithCompleteAcquireActions(Data->HasField(ANSI_TO_TCHAR("completeAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("completeAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("completeAcquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("completeAcquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithChallengePeriodEventId(Data->HasField(ANSI_TO_TCHAR("challengePeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengePeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPremiseMissionTaskName(Data->HasField(ANSI_TO_TCHAR("premiseMissionTaskName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("premiseMissionTaskName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCounterName(Data->HasField(ANSI_TO_TCHAR("counterName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("counterName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetResetType(Data->HasField(ANSI_TO_TCHAR("targetResetType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetResetType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetValue(Data->HasField(ANSI_TO_TCHAR("targetValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("targetValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FMissionTaskModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MissionTaskIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("missionTaskId"), MissionTaskIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (VerifyCompleteTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyCompleteType"), VerifyCompleteTypeValue.GetValue());
        }
        if (TargetCounterValue != nullptr && TargetCounterValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("targetCounter"), TargetCounterValue->ToJson());
        }
        if (VerifyCompleteConsumeActionsValue != nullptr && VerifyCompleteConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyCompleteConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("verifyCompleteConsumeActions"), v);
        }
        if (CompleteAcquireActionsValue != nullptr && CompleteAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CompleteAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("completeAcquireActions"), v);
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("challengePeriodEventId"), ChallengePeriodEventIdValue.GetValue());
        }
        if (PremiseMissionTaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("premiseMissionTaskName"), PremiseMissionTaskNameValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("counterName"), CounterNameValue.GetValue());
        }
        if (TargetResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("targetResetType"), TargetResetTypeValue.GetValue());
        }
        if (TargetValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("targetValue"), FString::Printf(TEXT("%lld"), TargetValueValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FMissionTaskModel::TypeName = "MissionTaskModel";
}
#include "Mission/Model/Cache/MissionTaskModel.h"

namespace Gs2::Mission::Model::Cache
{
    FString FMissionTaskModelCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("mission:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentMissionGroupName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":MissionTaskModel");
    }

    FString FMissionTaskModelCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentMissionTaskName
    )
    {
        return
            FString()
            + CacheOwnerArgumentMissionTaskName.Get(FString())
            ;
    }

    bool FMissionTaskModelCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<FString> CacheOwnerArgumentMissionTaskName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Mission::Model::FMissionTaskModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Mission::Model::FMissionTaskModelPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Mission::Model::FMissionTaskModel>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentMissionGroupName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentMissionTaskName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FMissionTaskModelCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<FString> CacheOwnerArgumentMissionTaskName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Mission::Model::FMissionTaskModelPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentMissionGroupName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentMissionTaskName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Mission::Model::FMissionTaskModel::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FMissionTaskModelCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<FString> CacheOwnerArgumentMissionTaskName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Mission::Model::FMissionTaskModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentMissionGroupName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentMissionTaskName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<FString> CacheOwnerArgumentMissionTaskName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Mission::Model::FMissionTaskModelPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Mission::Model::FMissionTaskModelPtr* CacheOwnerArgumentOutItem
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
        Gs2::Mission::Model::FMissionTaskModelPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentMissionGroupName,
                CacheOwnerArgumentMissionTaskName,
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
            CacheOwnerArgumentMissionGroupName,
            CacheOwnerArgumentMissionTaskName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("missionTaskModel"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FMissionTaskModelCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Mission::Model::FMissionTaskModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentMissionGroupName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Mission::Model::FMissionTaskModelPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModel>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FMissionTaskModelCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentMissionGroupName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Mission::Model::FMissionTaskModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentMissionGroupName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}