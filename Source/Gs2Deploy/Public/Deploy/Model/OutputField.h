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
    class GS2DEPLOY_API FOutputField final : public TSharedFromThis<FOutputField>
    {
        TOptional<FString> NameValue;
        TOptional<FString> FieldNameValue;

    public:
        FOutputField();
        FOutputField(
            const FOutputField& From
        );
        ~FOutputField() = default;

        TSharedPtr<FOutputField> WithName(const TOptional<FString> Name);
        TSharedPtr<FOutputField> WithFieldName(const TOptional<FString> FieldName);

        TOptional<FString> GetName() const;
        TOptional<FString> GetFieldName() const;


        static TSharedPtr<FOutputField> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FOutputField, ESPMode::ThreadSafe> FOutputFieldPtr;
}