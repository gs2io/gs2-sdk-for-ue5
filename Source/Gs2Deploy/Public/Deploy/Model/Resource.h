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
#include "OutputField.h"

namespace Gs2::Deploy::Model
{
    class GS2DEPLOY_API FResource final : public FGs2Object, public TSharedFromThis<FResource>
    {
        TOptional<FString> ResourceIdValue;
        TOptional<FString> TypeValue;
        TOptional<FString> NameValue;
        TOptional<FString> RequestValue;
        TOptional<FString> ResponseValue;
        TOptional<FString> RollbackContextValue;
        TOptional<FString> RollbackRequestValue;
        TSharedPtr<TArray<FString>> RollbackAfterValue;
        TSharedPtr<TArray<TSharedPtr<FOutputField>>> OutputFieldsValue;
        TOptional<FString> WorkIdValue;
        TOptional<int64> CreatedAtValue;

    public:
        FResource();
        FResource(
            const FResource& From
        );
        virtual ~FResource() override = default;

        TSharedPtr<FResource> WithResourceId(const TOptional<FString> ResourceId);
        TSharedPtr<FResource> WithType(const TOptional<FString> Type);
        TSharedPtr<FResource> WithName(const TOptional<FString> Name);
        TSharedPtr<FResource> WithRequest(const TOptional<FString> Request);
        TSharedPtr<FResource> WithResponse(const TOptional<FString> Response);
        TSharedPtr<FResource> WithRollbackContext(const TOptional<FString> RollbackContext);
        TSharedPtr<FResource> WithRollbackRequest(const TOptional<FString> RollbackRequest);
        TSharedPtr<FResource> WithRollbackAfter(const TSharedPtr<TArray<FString>> RollbackAfter);
        TSharedPtr<FResource> WithOutputFields(const TSharedPtr<TArray<TSharedPtr<FOutputField>>> OutputFields);
        TSharedPtr<FResource> WithWorkId(const TOptional<FString> WorkId);
        TSharedPtr<FResource> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetResourceId() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetRequest() const;
        TOptional<FString> GetResponse() const;
        TOptional<FString> GetRollbackContext() const;
        TOptional<FString> GetRollbackRequest() const;
        TSharedPtr<TArray<FString>> GetRollbackAfter() const;
        TSharedPtr<TArray<TSharedPtr<FOutputField>>> GetOutputFields() const;
        TOptional<FString> GetWorkId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetStackNameFromGrn(const FString Grn);
        static TOptional<FString> GetResourceNameFromGrn(const FString Grn);

        static TSharedPtr<FResource> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FResource, ESPMode::ThreadSafe> FResourcePtr;
}