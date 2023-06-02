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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "BoxItem.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FBoxItems final : public Gs2Object, public TSharedFromThis<FBoxItems>
    {
        TOptional<FString> BoxIdValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<FBoxItem>>> ItemsValue;

    public:
        FBoxItems();
        FBoxItems(
            const FBoxItems& From
        );
        virtual ~FBoxItems() override = default;

        TSharedPtr<FBoxItems> WithBoxId(const TOptional<FString> BoxId);
        TSharedPtr<FBoxItems> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FBoxItems> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBoxItems> WithItems(const TSharedPtr<TArray<TSharedPtr<FBoxItem>>> Items);

        TOptional<FString> GetBoxId() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<TSharedPtr<FBoxItem>>> GetItems() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetPrizeTableNameFromGrn(const FString Grn);

        static TSharedPtr<FBoxItems> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBoxItems, ESPMode::ThreadSafe> FBoxItemsPtr;
}