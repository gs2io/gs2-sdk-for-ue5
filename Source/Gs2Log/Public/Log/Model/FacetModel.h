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

namespace Gs2::Log::Model
{
    class GS2LOG_API FFacetModel final : public FGs2Object, public TSharedFromThis<FFacetModel>
    {
        TOptional<FString> FacetModelIdValue;
        TOptional<FString> FieldValue;
        TOptional<FString> TypeValue;
        TOptional<FString> DisplayNameValue;
        TOptional<int32> OrderValue;

    public:
        FFacetModel();
        FFacetModel(
            const FFacetModel& From
        );
        virtual ~FFacetModel() override = default;

        TSharedPtr<FFacetModel> WithFacetModelId(const TOptional<FString> FacetModelId);
        TSharedPtr<FFacetModel> WithField(const TOptional<FString> Field);
        TSharedPtr<FFacetModel> WithType(const TOptional<FString> Type);
        TSharedPtr<FFacetModel> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FFacetModel> WithOrder(const TOptional<int32> Order);

        TOptional<FString> GetFacetModelId() const;
        TOptional<FString> GetField() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<int32> GetOrder() const;
        FString GetOrderString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetFieldFromGrn(const FString Grn);

        static TSharedPtr<FFacetModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFacetModel, ESPMode::ThreadSafe> FFacetModelPtr;
}