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

namespace Gs2::Deploy::Model
{
    class GS2DEPLOY_API FStack final : public TSharedFromThis<FStack>
    {
        TOptional<FString> StackIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> TemplateValue;
        TOptional<FString> StatusValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FStack();
        FStack(
            const FStack& From
        );
        ~FStack() = default;

        TSharedPtr<FStack> WithStackId(const TOptional<FString> StackId);
        TSharedPtr<FStack> WithName(const TOptional<FString> Name);
        TSharedPtr<FStack> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FStack> WithTemplate(const TOptional<FString> Template);
        TSharedPtr<FStack> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FStack> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStack> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetStackId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetTemplate() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetStackNameFromGrn(const FString Grn);

        static TSharedPtr<FStack> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStack, ESPMode::ThreadSafe> FStackPtr;
}