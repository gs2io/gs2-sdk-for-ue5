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
    class GS2CHAT_API FCategoryModelMaster final : public FGs2Object, public TSharedFromThis<FCategoryModelMaster>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> RejectAccessTokenPostValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FCategoryModelMaster();
        FCategoryModelMaster(
            const FCategoryModelMaster& From
        );
        virtual ~FCategoryModelMaster() override = default;

        TSharedPtr<FCategoryModelMaster> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModelMaster> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FCategoryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCategoryModelMaster> WithRejectAccessTokenPost(const TOptional<FString> RejectAccessTokenPost);
        TSharedPtr<FCategoryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCategoryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FCategoryModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetRejectAccessTokenPost() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModelMaster, ESPMode::ThreadSafe> FCategoryModelMasterPtr;
}