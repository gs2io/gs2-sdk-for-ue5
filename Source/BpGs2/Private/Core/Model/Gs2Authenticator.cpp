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

#include "Core/Model/Gs2Authenticator.h"

FGs2Authenticator UGs2AuthenticatorFunctionLibrary::CreateGs2Authenticator(
	const FGs2AccountNamespace Namespace,
	const FGs2KeyKey Key
)
{
	FGs2Authenticator Return;
	if (Namespace.Value == nullptr) {
		UE_LOG(BpGs2Log, Error, TEXT("[UGs2AuthenticatorFunctionLibrary::CreateGs2Authenticator] Namespace parameter specification is missing."))
		return Return;
	}
	Return.Value = MakeShared<Gs2::UE5::Util::FGs2AccountAuthenticator>(
		MakeShared<Gs2::UE5::Util::FAccountSetting>(
			*Namespace.Value->NamespaceName(),
			FString::Format(TEXT("grn:gs2:{region}:{ownerId}:key:{0}:key:{1}"), {Key.NamespaceName, Key.KeyName})
		)
	);
	return Return;
}
