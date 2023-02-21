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
#include "../Model/DataObject.h"

namespace Gs2::Datastore::Result
{
    class GS2DATASTORE_API FPrepareUploadByUserIdResult final : public TSharedFromThis<FPrepareUploadByUserIdResult>
    {
        TSharedPtr<Model::FDataObject> ItemValue;
        TOptional<FString> UploadUrlValue;
        
    public:
        
        FPrepareUploadByUserIdResult();
        FPrepareUploadByUserIdResult(
            const FPrepareUploadByUserIdResult& From
        );
        ~FPrepareUploadByUserIdResult() = default;

        TSharedPtr<FPrepareUploadByUserIdResult> WithItem(const TSharedPtr<Model::FDataObject> Item);
        TSharedPtr<FPrepareUploadByUserIdResult> WithUploadUrl(const TOptional<FString> UploadUrl);

        TSharedPtr<Model::FDataObject> GetItem() const;
        TOptional<FString> GetUploadUrl() const;

        static TSharedPtr<FPrepareUploadByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareUploadByUserIdResult, ESPMode::ThreadSafe> FPrepareUploadByUserIdResultPtr;
}