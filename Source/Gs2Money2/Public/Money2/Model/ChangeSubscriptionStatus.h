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

namespace Gs2::Money2::Model
{
	class GS2MONEY2_API FChangeSubscriptionStatus : public TSharedFromThis<FChangeSubscriptionStatus>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ContentNameValue;

        TSharedPtr<FChangeSubscriptionStatus> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FChangeSubscriptionStatus> WithUserId(
            const TOptional<FString> UserId
        );
        TOptional<FString> GetUserId() const;

        TSharedPtr<FChangeSubscriptionStatus> WithContentName(
            const TOptional<FString> ContentName
        );
        TOptional<FString> GetContentName() const;

        static TSharedPtr<FChangeSubscriptionStatus> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FChangeSubscriptionStatus> FChangeSubscriptionStatusPtr;
}
