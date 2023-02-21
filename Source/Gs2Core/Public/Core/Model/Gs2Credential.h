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

typedef FString FGs2ClientId;
typedef FString FGs2ClientSecret;
typedef FString FGs2ProjectToken;

namespace Gs2::Core::Model
{
	class GS2CORE_API IGs2Credential
	{
	public:
		virtual ~IGs2Credential() {};

		virtual const FGs2ClientId& ClientId() const = 0;
		
		virtual const FGs2ClientSecret& ClientSecret() const = 0;
		
		virtual const FGs2ProjectToken& ProjectToken() const = 0;

		virtual void UpdateProjectToken(const FGs2ProjectToken& Token) = 0;
	};
	typedef TSharedPtr<IGs2Credential, ESPMode::ThreadSafe> FGs2CredentialPtr;
}