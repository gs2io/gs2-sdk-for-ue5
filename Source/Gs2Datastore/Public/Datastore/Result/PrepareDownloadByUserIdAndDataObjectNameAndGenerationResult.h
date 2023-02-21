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
    class GS2DATASTORE_API FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult final : public TSharedFromThis<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult>
    {
        TSharedPtr<Model::FDataObject> ItemValue;
        TOptional<FString> FileUrlValue;
        TOptional<int64> ContentLengthValue;
        
    public:
        
        FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult();
        FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult(
            const FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult& From
        );
        ~FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult() = default;

        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult> WithItem(const TSharedPtr<Model::FDataObject> Item);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult> WithFileUrl(const TOptional<FString> FileUrl);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult> WithContentLength(const TOptional<int64> ContentLength);

        TSharedPtr<Model::FDataObject> GetItem() const;
        TOptional<FString> GetFileUrl() const;
        TOptional<int64> GetContentLength() const;
        FString GetContentLengthString() const;

        static TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResult, ESPMode::ThreadSafe> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationResultPtr;
}