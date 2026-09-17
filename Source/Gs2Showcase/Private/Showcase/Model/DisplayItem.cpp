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

#include "Showcase/Model/DisplayItem.h"

namespace Gs2::Showcase::Model
{
    FDisplayItem::FDisplayItem():
        DisplayItemIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        SalesItemValue(nullptr),
        SalesItemGroupValue(nullptr),
        SalesPeriodEventIdValue(TOptional<FString>())
    {
    }

    FDisplayItem::FDisplayItem(
        const FDisplayItem& From
    ):
        DisplayItemIdValue(From.DisplayItemIdValue),
        TypeValue(From.TypeValue),
        SalesItemValue(From.SalesItemValue),
        SalesItemGroupValue(From.SalesItemGroupValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue)
    {
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithDisplayItemId(
        const TOptional<FString> DisplayItemId
    )
    {
        this->DisplayItemIdValue = DisplayItemId;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesItem(
        const TSharedPtr<FSalesItem> SalesItem
    )
    {
        this->SalesItemValue = SalesItem;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesItemGroup(
        const TSharedPtr<FSalesItemGroup> SalesItemGroup
    )
    {
        this->SalesItemGroupValue = SalesItemGroup;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FDisplayItem::GetDisplayItemId() const
    {
        return DisplayItemIdValue;
    }
    TOptional<FString> FDisplayItem::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<FSalesItem> FDisplayItem::GetSalesItem() const
    {
        return SalesItemValue;
    }
    TSharedPtr<FSalesItemGroup> FDisplayItem::GetSalesItemGroup() const
    {
        return SalesItemGroupValue;
    }
    TOptional<FString> FDisplayItem::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }

    TSharedPtr<FDisplayItem> FDisplayItem::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDisplayItem>()
            ->WithDisplayItemId(Data->HasField(ANSI_TO_TCHAR("displayItemId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayItemId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItem(Data->HasField(ANSI_TO_TCHAR("salesItem")) ? [Data]() -> Model::FSalesItemPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("salesItem")))
                    {
                        return nullptr;
                    }
                    return Model::FSalesItem::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("salesItem")));
                 }() : nullptr)
            ->WithSalesItemGroup(Data->HasField(ANSI_TO_TCHAR("salesItemGroup")) ? [Data]() -> Model::FSalesItemGroupPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("salesItemGroup")))
                    {
                        return nullptr;
                    }
                    return Model::FSalesItemGroup::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("salesItemGroup")));
                 }() : nullptr)
            ->WithSalesPeriodEventId(Data->HasField(ANSI_TO_TCHAR("salesPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("salesPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDisplayItem::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DisplayItemIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("displayItemId"), DisplayItemIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("type"), TypeValue.GetValue());
        }
        if (SalesItemValue != nullptr && SalesItemValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("salesItem"), SalesItemValue->ToJson());
        }
        if (SalesItemGroupValue != nullptr && SalesItemGroupValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("salesItemGroup"), SalesItemGroupValue->ToJson());
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("salesPeriodEventId"), SalesPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FDisplayItem::TypeName = "DisplayItem";
}
#include "Showcase/Model/Cache/DisplayItem.h"

namespace Gs2::Showcase::Model::Cache
{
    FString FDisplayItemCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("showcase:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentUserId.Get(FString()) + FString(":")
            + CacheOwnerArgumentShowcaseName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":DisplayItem");
    }

    FString FDisplayItemCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentDisplayItemId
    )
    {
        return
            FString()
            + CacheOwnerArgumentDisplayItemId.Get(FString())
            ;
    }

    bool FDisplayItemCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<FString> CacheOwnerArgumentDisplayItemId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Showcase::Model::FDisplayItemPtr* CacheOwnerArgumentOutItem
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
        Gs2::Showcase::Model::FDisplayItemPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Showcase::Model::FDisplayItem>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentShowcaseName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentDisplayItemId
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FDisplayItemCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<FString> CacheOwnerArgumentDisplayItemId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Showcase::Model::FDisplayItemPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentShowcaseName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentDisplayItemId
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Showcase::Model::FDisplayItem::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FDisplayItemCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<FString> CacheOwnerArgumentDisplayItemId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        CacheSnapshot->Delete(Gs2::Showcase::Model::FDisplayItem::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentShowcaseName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentDisplayItemId
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<FString> CacheOwnerArgumentDisplayItemId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Showcase::Model::FDisplayItemPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Showcase::Model::FDisplayItemPtr* CacheOwnerArgumentOutItem
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
        Gs2::Showcase::Model::FDisplayItemPtr CacheOwnerFetchedItem;
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
                CacheOwnerArgumentShowcaseName,
                CacheOwnerArgumentDisplayItemId,
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
            CacheOwnerArgumentShowcaseName,
            CacheOwnerArgumentDisplayItemId,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("displayItem"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FDisplayItemCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Showcase::Model::FDisplayItemPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Showcase::Model::FDisplayItem::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentShowcaseName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Showcase::Model::FDisplayItemPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Showcase::Model::FDisplayItem>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FDisplayItemCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentShowcaseName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Showcase::Model::FDisplayItem::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentShowcaseName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}