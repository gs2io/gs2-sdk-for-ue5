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

namespace Gs2::Deploy::Model
{
    class GS2DEPLOY_API FEvent final : public Gs2Object, public TSharedFromThis<FEvent>
    {
        TOptional<FString> EventIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> ResourceNameValue;
        TOptional<FString> TypeValue;
        TOptional<FString> MessageValue;
        TOptional<int64> EventAtValue;
        TOptional<int64> RevisionValue;

    public:
        FEvent();
        FEvent(
            const FEvent& From
        );
        virtual ~FEvent() override = default;

        TSharedPtr<FEvent> WithEventId(const TOptional<FString> EventId);
        TSharedPtr<FEvent> WithName(const TOptional<FString> Name);
        TSharedPtr<FEvent> WithResourceName(const TOptional<FString> ResourceName);
        TSharedPtr<FEvent> WithType(const TOptional<FString> Type);
        TSharedPtr<FEvent> WithMessage(const TOptional<FString> Message);
        TSharedPtr<FEvent> WithEventAt(const TOptional<int64> EventAt);
        TSharedPtr<FEvent> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetEventId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetResourceName() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetMessage() const;
        TOptional<int64> GetEventAt() const;
        FString GetEventAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetStackNameFromGrn(const FString Grn);
        static TOptional<FString> GetEventNameFromGrn(const FString Grn);

        static TSharedPtr<FEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEvent, ESPMode::ThreadSafe> FEventPtr;
}