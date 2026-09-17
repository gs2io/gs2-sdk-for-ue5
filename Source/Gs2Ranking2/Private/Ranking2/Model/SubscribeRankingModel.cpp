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

#include "Ranking2/Model/SubscribeRankingModel.h"

namespace Gs2::Ranking2::Model
{
    FSubscribeRankingModel::FSubscribeRankingModel():
        SubscribeRankingModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        OrderDirectionValue(TOptional<FString>()),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>())
    {
    }

    FSubscribeRankingModel::FSubscribeRankingModel(
        const FSubscribeRankingModel& From
    ):
        SubscribeRankingModelIdValue(From.SubscribeRankingModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        OrderDirectionValue(From.OrderDirectionValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue)
    {
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithSubscribeRankingModelId(
        const TOptional<FString> SubscribeRankingModelId
    )
    {
        this->SubscribeRankingModelIdValue = SubscribeRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FSubscribeRankingModel::GetSubscribeRankingModelId() const
    {
        return SubscribeRankingModelIdValue;
    }
    TOptional<FString> FSubscribeRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSubscribeRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FSubscribeRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FSubscribeRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FSubscribeRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FSubscribeRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FSubscribeRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FSubscribeRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FSubscribeRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FSubscribeRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FSubscribeRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    TOptional<FString> FSubscribeRankingModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):subscribe:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeRankingModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):subscribe:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeRankingModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):subscribe:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeRankingModel::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):subscribe:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSubscribeRankingModel> FSubscribeRankingModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubscribeRankingModel>()
            ->WithSubscribeRankingModelId(Data->HasField(ANSI_TO_TCHAR("subscribeRankingModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subscribeRankingModelId"), v))
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
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSubscribeRankingModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SubscribeRankingModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("subscribeRankingModelId"), SubscribeRankingModelIdValue.GetValue());
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
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("accessPeriodEventId"), AccessPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FSubscribeRankingModel::TypeName = "SubscribeRankingModel";
}
#include "Ranking2/Model/Cache/SubscribeRankingModel.h"

namespace Gs2::Ranking2::Model::Cache
{
    FString FSubscribeRankingModelCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("ranking2:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":SubscribeRankingModel");
    }

    FString FSubscribeRankingModelCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentRankingName
    )
    {
        return
            FString()
            + CacheOwnerArgumentRankingName.Get(FString())
            ;
    }

    bool FSubscribeRankingModelCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Ranking2::Model::FSubscribeRankingModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Ranking2::Model::FSubscribeRankingModelPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Ranking2::Model::FSubscribeRankingModel>(
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

    void FSubscribeRankingModelCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Ranking2::Model::FSubscribeRankingModelPtr& CacheOwnerArgumentItem
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
        CacheSnapshot->Put(Gs2::Ranking2::Model::FSubscribeRankingModel::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FSubscribeRankingModelCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Ranking2::Model::FSubscribeRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentRankingName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeRankingModelCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRankingName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking2::Model::FSubscribeRankingModelPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Ranking2::Model::FSubscribeRankingModelPtr* CacheOwnerArgumentOutItem
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
        Gs2::Ranking2::Model::FSubscribeRankingModelPtr CacheOwnerFetchedItem;
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
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("subscribeRankingModel"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FSubscribeRankingModelCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Ranking2::Model::FSubscribeRankingModelPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Ranking2::Model::FSubscribeRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Ranking2::Model::FSubscribeRankingModelPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingModel>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FSubscribeRankingModelCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Ranking2::Model::FSubscribeRankingModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}