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

#include "Ranking2/Model/GlobalRankingModel.h"

namespace Gs2::Ranking2::Model
{
    FGlobalRankingModel::FGlobalRankingModel():
        GlobalRankingModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        OrderDirectionValue(TOptional<FString>()),
        EntryPeriodEventIdValue(TOptional<FString>()),
        RankingRewardsValue(nullptr),
        AccessPeriodEventIdValue(TOptional<FString>()),
        RewardCalculationIndexValue(TOptional<FString>())
    {
    }

    FGlobalRankingModel::FGlobalRankingModel(
        const FGlobalRankingModel& From
    ):
        GlobalRankingModelIdValue(From.GlobalRankingModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        OrderDirectionValue(From.OrderDirectionValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        RankingRewardsValue(From.RankingRewardsValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue),
        RewardCalculationIndexValue(From.RewardCalculationIndexValue)
    {
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithGlobalRankingModelId(
        const TOptional<FString> GlobalRankingModelId
    )
    {
        this->GlobalRankingModelIdValue = GlobalRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithRankingRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewards
    )
    {
        this->RankingRewardsValue = RankingRewards;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::WithRewardCalculationIndex(
        const TOptional<FString> RewardCalculationIndex
    )
    {
        this->RewardCalculationIndexValue = RewardCalculationIndex;
        return SharedThis(this);
    }
    TOptional<FString> FGlobalRankingModel::GetGlobalRankingModelId() const
    {
        return GlobalRankingModelIdValue;
    }
    TOptional<FString> FGlobalRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGlobalRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FGlobalRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FGlobalRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FGlobalRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FGlobalRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FGlobalRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FGlobalRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FGlobalRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FGlobalRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> FGlobalRankingModel::GetRankingRewards() const
    {
        return RankingRewardsValue;
    }
    TOptional<FString> FGlobalRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }
    TOptional<FString> FGlobalRankingModel::GetRewardCalculationIndex() const
    {
        return RewardCalculationIndexValue;
    }

    TOptional<FString> FGlobalRankingModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingModel::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):global:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGlobalRankingModel> FGlobalRankingModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalRankingModel>()
            ->WithGlobalRankingModelId(Data->HasField(ANSI_TO_TCHAR("globalRankingModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalRankingModelId"), v))
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
            ->WithMinimumValue(Data->HasField(ANSI_TO_TCHAR("minimumValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minimumValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaximumValue(Data->HasField(ANSI_TO_TCHAR("maximumValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithSum(Data->HasField(ANSI_TO_TCHAR("sum")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sum"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithOrderDirection(Data->HasField(ANSI_TO_TCHAR("orderDirection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderDirection"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEntryPeriodEventId(Data->HasField(ANSI_TO_TCHAR("entryPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("entryPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRankingRewards(Data->HasField(ANSI_TO_TCHAR("rankingRewards")) ? [Data]() -> TSharedPtr<TArray<Model::FRankingRewardPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRankingRewardPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rankingRewards")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("rankingRewards")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("rankingRewards")))
                        {
                            v->Add(Model::FRankingReward::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRankingRewardPtr>>())
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRewardCalculationIndex(Data->HasField(ANSI_TO_TCHAR("rewardCalculationIndex")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rewardCalculationIndex"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGlobalRankingModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GlobalRankingModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("globalRankingModelId"), GlobalRankingModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (MinimumValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("minimumValue"), FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue()));
        }
        if (MaximumValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("maximumValue"), FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue()));
        }
        if (SumValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("sum"), SumValue.GetValue());
        }
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("orderDirection"), OrderDirectionValue.GetValue());
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("entryPeriodEventId"), EntryPeriodEventIdValue.GetValue());
        }
        if (RankingRewardsValue != nullptr && RankingRewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RankingRewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("rankingRewards"), v);
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("accessPeriodEventId"), AccessPeriodEventIdValue.GetValue());
        }
        if (RewardCalculationIndexValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("rewardCalculationIndex"), RewardCalculationIndexValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGlobalRankingModel::TypeName = "GlobalRankingModel";
}
#include "Ranking2/Model/Cache/GlobalRankingModel.h"

namespace Gs2::Ranking2::Model::Cache
{
    FString FGlobalRankingModelCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("ranking2:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":GlobalRankingModel");
    }

    FString FGlobalRankingModelCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentRankingName
    )
    {
        return
            FString()
            + CacheOwnerArgumentRankingName.Get(FString())
            ;
    }

    bool FGlobalRankingModelCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Ranking2::Model::FGlobalRankingModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Ranking2::Model::FGlobalRankingModelPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Ranking2::Model::FGlobalRankingModel>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentRankingName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FGlobalRankingModelCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Ranking2::Model::FGlobalRankingModelPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentRankingName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Ranking2::Model::FGlobalRankingModel::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FGlobalRankingModelCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Ranking2::Model::FGlobalRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentRankingName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingModelCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking2::Model::FGlobalRankingModelPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Ranking2::Model::FGlobalRankingModelPtr* CacheOwnerArgumentOutItem
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
        Gs2::Ranking2::Model::FGlobalRankingModelPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentRankingName,
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
            CacheOwnerArgumentRankingName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("globalRankingModel"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingModelCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Ranking2::Model::FGlobalRankingModelPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Ranking2::Model::FGlobalRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Ranking2::Model::FGlobalRankingModelPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingModel>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FGlobalRankingModelCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Ranking2::Model::FGlobalRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}