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

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FReferenceOf final : public Gs2Object, public TSharedFromThis<FReferenceOf>
    {
        TOptional<FString> ReferenceOfIdValue;
        TOptional<FString> NameValue;

    public:
        FReferenceOf();
        FReferenceOf(
            const FReferenceOf& From
        );
        virtual ~FReferenceOf() override = default;

        TSharedPtr<FReferenceOf> WithReferenceOfId(const TOptional<FString> ReferenceOfId);
        TSharedPtr<FReferenceOf> WithName(const TOptional<FString> Name);

        TOptional<FString> GetReferenceOfId() const;
        TOptional<FString> GetName() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemSetNameFromGrn(const FString Grn);
        static TOptional<FString> GetReferenceOfFromGrn(const FString Grn);

        static TSharedPtr<FReferenceOf> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReferenceOf, ESPMode::ThreadSafe> FReferenceOfPtr;
}