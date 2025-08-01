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

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FCategoryModel final : public FGs2Object, public TSharedFromThis<FCategoryModel>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> RejectAccessTokenPostValue;

    public:
        FCategoryModel();
        FCategoryModel(
            const FCategoryModel& From
        );
        virtual ~FCategoryModel() override = default;

        TSharedPtr<FCategoryModel> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModel> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FCategoryModel> WithRejectAccessTokenPost(const TOptional<FString> RejectAccessTokenPost);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetRejectAccessTokenPost() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModel, ESPMode::ThreadSafe> FCategoryModelPtr;
}